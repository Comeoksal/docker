# docker
SystemProgramming, NetworkProgramming by Docker
## How To Connect SSH
1. ssh-keygen -t ed25519 -C "your_email@example.com" (docker bash)
2. cat ~/.ssh/id_ed25519.pub (copy text and paste https://github.com/settings/keys)
3. git remote set-url origin git@github.com:Comeoksal/docker.git (docker bash)
apt update
apt install -y openssh-client
4. eval "$(ssh-agent -s)" (docker bash)
5. ssh-add ~/.ssh/id_ed25519 (docker bash)
6. ssh -T git@github.com
7. git push origin main
