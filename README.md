# Installation und Einrichtung

## Windows:

1. [BSuSP Image herunterladen](https://uni-duesseldorf.sciebo.de/s/55xwyumuCKrfoJk/download) (Passwort: bs4student)
2. [Virtual Box installieren](https://download.virtualbox.org/virtualbox/7.1.6/VirtualBox-7.1.6-167084-Win.exe) (ggf. Neustart erforderlich)
3. In Virtual Box → Import → .ova Image importieren (ggf. Name anpassen)
4. In den Einstellungen der VM folgende Änderungen vornehmen:
    - General → Advanced → Shared Clipboard → Bidirectional (um kopieren zu können)
    - Display → Screen → Graphics Controller → VMSVGA and Display → Screen → Video Memory → 128 MB (für flüssiges Bild / Vollbild)
    - Storage → Devices → Controller: SATA → CD Icon + → VBoxGuestAdditions.iso → Choose
    
    Alles mit “OK” bestätigen und speichern
    
5. VM booten und einloggen (Username: student, Passwort: bs4student)
    
    <aside>
    ⚠️
    
    **Nicht die VM updaten! Diese Version ist vorausgesetzt für das Modul!**
    
    </aside>
    
6. Im Terminal ausführen:
    
    ```bash
    sudo mount /dev/cdrom /mnt
    ```
    
    ```bash
    sudo /mnt/VBoxLinuxAdditions.run
    ```
    
    ```bash
    reboot
    ```
    
7. Speicherplatz frei geben (Optional):
    
    ```bash
    sudo apt clean
    ```
    
    ```bash
    sudo apt autoclean
    ```
    
    ```bash
    sudo apt autoremove
    ```
    

---

## Verbindung mit GitHub (optional)

1. Git installieren:
    
    ```bash
    sudo apt install git
    ```
    
2. Git konfigurieren:
    
    ```bash
    git config --global user.name "Your Name"
    ```
    
    ```bash
    git config --global user.email "your-email@example.com"
    ```
    
3. SSH-key generieren:
    
    ```bash
    ssh-keygen -t rsa -b 4096 -C "your-email@example.com"
    ```
    
    ```bash
    eval "$(ssh-agent -s)"
    ```
    
    ```bash
    ssh-add ~/.ssh/id_rsa
    ```
    
    ```bash
    cat ~/.ssh/id_rsa.pub
    ```
    
4. Bei GitHub SSH-key hinzufügen:
    - Settings → SSH and GPG keys → New SSH key
5. Verbindung prüfen:
    
    ```bash
    ssh -T git@github.com
    ```
    
6. Repository downloaden:
    
    ```bash
    git clone git@github.com:MaxBRheinl/bs-sp-hhu.git
    ```
