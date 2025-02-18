import os
import platform
import subprocess

def clear_memory_cache():
    system = platform.system()

    if system == "Windows":
        try:
            print("[+] Flushing DNS cache...")
            subprocess.run("ipconfig /flushdns", shell=True, check=True)
            
            print("[+] Clearing standby memory (requires admin)...")
            subprocess.run('powershell.exe -Command "Clear-MemoryCache"', shell=True, check=True)

            print("[+] Enabling ClearPageFileAtShutdown (takes effect after reboot)...")
            subprocess.run('reg add "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management" /v ClearPageFileAtShutdown /t REG_DWORD /d 1 /f', shell=True, check=True)

            print("[+] Windows cache cleared successfully. Some changes take effect after reboot.")
        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    elif system == "Linux":
        try:
            print("[+] Syncing and clearing memory cache (requires sudo)...")
            subprocess.run("sync && echo 3 | sudo tee /proc/sys/vm/drop_caches", shell=True, check=True)
            print("[+] Linux memory cache cleared.")
        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    elif system == "Darwin":  # macOS
        try:
            print("[+] Running purge command (requires sudo)...")
            subprocess.run("sudo purge", shell=True, check=True)
            print("[+] macOS memory cache cleared.")
        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    else:
        print("[-] Unsupported OS.")

if __name__ == "__main__":
    clear_memory_cache()
