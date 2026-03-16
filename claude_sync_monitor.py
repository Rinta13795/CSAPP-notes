#!/usr/bin/env python3
import time
import re
import shutil
from pathlib import Path
from datetime import datetime

DOWNLOAD_PATH = Path.home() / "Downloads"
TARGET_PATH = Path.home() / "Desktop" / "Claude_聊天记录"
FILE_RE = re.compile(r"^Claude_(?P<cid>.+?)(?: \(\d+\))?\.md$")


def log(msg):
    print(f"[{datetime.now().strftime('%H:%M:%S')}] {msg}", flush=True)


def extract_cid(filename: str):
    m = FILE_RE.match(filename)
    return m.group("cid") if m else None


def monitor():
    TARGET_PATH.mkdir(parents=True, exist_ok=True)
    log(f"Monitoring: {DOWNLOAD_PATH}")
    log(f"Target dir: {TARGET_PATH}")

    while True:
        try:
            files = [f for f in DOWNLOAD_PATH.glob("Claude_*.md") if extract_cid(f.name)]
            if files:
                grouped = {}
                for f in files:
                    cid = extract_cid(f.name)
                    grouped.setdefault(cid, []).append(f)

                for cid, group in grouped.items():
                    latest = max(group, key=lambda f: f.stat().st_mtime)
                    target = TARGET_PATH / f"Claude_{cid}.md"

                    shutil.copy2(latest, target)
                    log(f"SYNC cid={cid}  {latest.name} -> {target.name}")

                    for f in group:
                        try:
                            f.unlink()
                            log(f"CLEAN {f.name}")
                        except Exception as e:
                            log(f"SKIP clean {f.name}: {e}")

            time.sleep(2)

        except KeyboardInterrupt:
            log("Stopped by user")
            break
        except Exception as e:
            log(f"ERROR: {e}")
            time.sleep(5)


if __name__ == "__main__":
    monitor()
