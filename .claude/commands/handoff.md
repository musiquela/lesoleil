---
description: "Execute Session End Protocol - updates docs and commits"
---

# Session Handoff Protocol

You are executing the `/handoff` command. This command:

1. **Creates manual backup archive**
2. **Updates session context documentation**
3. **Commits all changes to git**
4. **Pushes to GitHub**
5. **Sends macOS notification**

## Step 1: Create Manual Backup Archive

```bash
cd /Users/keegandewitt/Cursor
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
mkdir -p _Backups
zip -r "_Backups/soleil_manual_$TIMESTAMP.zip" soleil \
  -x "*/.git/*" \
  -x "*/__pycache__/*" \
  -x "*.pyc" \
  -x "*.DS_Store" \
  -x "*/builds/*"
```

## Step 2: Update docs/context/CONTEXT.md

Update the session handoff documentation with:
- Current timestamp
- Session status (✅ COMPLETE / ⏳ IN PROGRESS / ⚠️ BLOCKED)
- Session accomplishments summary
- Git status (branch, commit hash, working tree status)
- Active work and recently modified files
- Next session tasks

## Step 3: Commit Session Documentation

```bash
git add docs/context/CONTEXT.md <any-new-files>
git commit -m "docs: Update session handoff (Session N complete)

🤖 Generated with Claude Code (https://claude.com/claude-code)

Co-Authored-By: Claude <noreply@anthropic.com>"
```

## Step 4: Push to GitHub

```bash
git push origin main
```

If push fails due to divergent branches:
```bash
git pull --rebase origin main
git push origin main
```

## Step 5: Send macOS Notification

```bash
osascript -e 'display notification "Session handoff complete. CONTEXT.md updated and pushed." with title "Soleil Project"'
```

## Step 6: Display Handoff Summary

Show the user:
- Session accomplishments
- Commits created and pushed
- Backup location
- Next session priorities

---

**IMPORTANT: Execute ALL steps sequentially. Do not skip the push step.**
