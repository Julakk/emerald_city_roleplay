# 🤝 Contributing to Emerald City Roleplay

Thank you for your interest in contributing to **Emerald City Roleplay (ECRP)**.

We welcome developers and contributors who want to help improve the server, documentation, tools, and overall player experience.

---

## 📋 Before Contributing

Before making a contribution:

- Read the project documentation.
- Check existing Issues and Pull Requests.
- Make sure your contribution does not duplicate existing work.
- Never include passwords, API keys, database credentials, tokens, or other sensitive information.
- Do not submit malicious code, exploits, backdoors, or intentionally harmful changes.

---

## 🌿 Branching

Please avoid committing directly to the main branch.

Recommended branch naming:

```text
feature/add-new-system
fix/fix-vehicle-bug
security/fix-sql-injection
docs/update-rules
refactor/improve-function
```

---

## 💻 Development Guidelines

When working on ECRP:

- Keep code clean and readable.
- Follow the existing project structure.
- Avoid unnecessary changes outside the scope of your contribution.
- Validate user input properly.
- Use safe database queries and escape user-controlled input.
- Perform permission checks for administrative or privileged commands.
- Avoid introducing unnecessary global or static state.
- Consider performance and server stability.
- Test changes before submitting them.

Security-sensitive changes should receive additional review before deployment.

---

## 📝 Commit Convention

Use clear and descriptive commit messages.

Recommended format:

```text
type: short description
```

Examples:

```text
fix: prevent vehicle duplication
feat: add new faction system
security: fix SQL injection in UCP register
docs: update server rules
refactor: improve vehicle storage system
```

Common types:

| Type | Usage |
|---|---|
| `feat` | New feature |
| `fix` | Bug fix |
| `security` | Security improvement |
| `refactor` | Code restructuring |
| `docs` | Documentation |
| `perf` | Performance improvement |
| `chore` | Maintenance |

---

## 🔧 Pull Requests

Before opening a Pull Request:

1. Make sure your changes are tested.
2. Explain what was changed.
3. Explain why the change was needed.
4. Include screenshots or logs when useful.
5. Mention related Issues when applicable.
6. Make sure no sensitive information is included.

A Pull Request may be reviewed, modified, rejected, or merged by the ECRP Development Team.

---

## 🐛 Bug Reports

For bugs, please provide:

- Clear description of the issue.
- Steps to reproduce.
- Expected behavior.
- Actual behavior.
- Screenshots or video if available.
- Relevant logs or error messages.

For security vulnerabilities, **do not create a public Issue**. Follow the instructions in [`SECURITY.md`](../SECURITY.md).

---

## 💡 Feature Requests

Feature suggestions are welcome.

A good feature request should explain:

- What the feature does.
- Why it is useful.
- How it could work.
- Potential impact on gameplay or performance.

---

## 🔐 Security

Never publicly disclose an exploitable security vulnerability before it has been reviewed and fixed.

Please read [`SECURITY.md`](../SECURITY.md) for the official vulnerability reporting procedure.

---

## ⚖️ Contribution Rules

By contributing to this project, you agree to:

- Respect other contributors.
- Keep discussions constructive.
- Follow project rules and decisions.
- Avoid harassment, discrimination, or toxic behavior.
- Respect the ECRP development process.

The ECRP Team reserves the right to reject contributions that do not meet project standards.

---

## 🌆 Emerald City Roleplay

**Build Your Story. Become Part of Emerald City.**

Thank you for helping us build a better Emerald City Roleplay experience.
