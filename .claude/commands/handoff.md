---
description: "Execute Session End Protocol - updates docs and commits"
---

# Session Handoff Protocol

You are executing the `/handoff` command. This command:

1. **Summarizes the current session work**
2. **Updates key project documentation**
3. **Creates a startup brief for the next Claude instance**
4. **Commits all changes to git**
5. **Pushes to GitHub: https://github.com/musiquela/lesoleil**

## Step 1: Generate Session Summary

Create a comprehensive summary of what was accomplished in this session, including:
- Major milestones achieved
- Code files created/modified
- Issues resolved
- Key decisions made
- Test results and verification

## Step 2: Update Project Context

Update or create these files:
- `PROJECT_STATUS.md` - Current state of the project
- `NEXT_SESSION.md` - Startup brief for next Claude instance
- `CHANGELOG.md` - Append session changes

## Step 3: Commit and Push

Execute git operations:
```bash
git add .
git commit -m "[Session End] <summary of work>"
git push origin main
```

If the push fails due to divergent branches, use:
```bash
git pull --rebase origin main
git push origin main
```

## Step 4: Display Handoff Report

Show the user:
- Session summary
- Files changed
- Commit hash
- Push status
- Next session priorities

---

**Execute all steps sequentially. Do not skip any step.**
