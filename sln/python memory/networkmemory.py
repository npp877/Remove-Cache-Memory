import os
import platform
import subprocess

def clear_network_memory_cache():
    system = platform.system()

    if system == "Windows":
        try:
            print("[+] Flushing DNS cache...")
            subprocess.run("ipconfig /flushdns", shell=True, check=True)

            print("[+] Resetting TCP/IP stack...")
            subprocess.run("netsh int ip reset", shell=True, check=True)

            print("[+] Clearing ARP cache...")
            subprocess.run("netsh interface ip delete arpcache", shell=True, check=True)

            print("[+] Releasing and renewing IP address...")
            subprocess.run("ipconfig /release && ipconfig /renew", shell=True, check=True)

            print("[+] Windows network cache cleared successfully.")

        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    elif system == "Linux":
        try:
            print("[+] Flushing DNS cache...")
            subprocess.run("sudo systemd-resolve --flush-caches", shell=True, check=True)

            print("[+] Clearing ARP cache...")
            subprocess.run("sudo ip -s -s neigh flush all", shell=True, check=True)

            print("[+] Clearing socket and route cache...")
            subprocess.run("sudo sysctl -w net.ipv4.route.flush=1", shell=True, check=True)

            print("[+] Restarting network service...")
            subprocess.run("sudo systemctl restart NetworkManager", shell=True, check=True)

            print("[+] Linux network cache cleared successfully.")

        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    elif system == "Darwin":  # macOS
        try:
            print("[+] Flushing DNS cache...")
            subprocess.run("sudo killall -HUP mDNSResponder", shell=True, check=True)

            print("[+] Clearing ARP cache...")
            subprocess.run("sudo arp -d -a", shell=True, check=True)

            print("[+] Restarting network service...")
            subprocess.run("sudo ifconfig en0 down && sudo ifconfig en0 up", shell=True, check=True)

            print("[+] macOS network cache cleared successfully.")

        except subprocess.CalledProcessError as e:
            print(f"[-] Error: {e}")

    else:
        print("[-] Unsupported OS.")

if __name__ == "__main__":
    clear_network_memory_cache()
