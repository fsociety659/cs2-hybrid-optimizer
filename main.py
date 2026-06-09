import os
import multiprocessing
import ctypes
import sys
import winreg

def is_admin():
    try:
        return ctypes.windll.shell32.IsUserAnAdmin()
    except:
        return False

def main():
    strings_db = {
        "en": {
            "title": "CS 2 HYBRID OPTIMIZER (Python + C)",
            "launch": "👉 FORMED LAUNCH OPTIONS:",
            "checking": "[...] Preparing system and closing background CS2...",
            "call_c_gpu": "[...] C-Motor: Resetting GPU shader cache...",
            "call_c_steam": "[...] C-Motor: Clearing Steam shader cache (ID 730)...",
            "call_c_ram": "[...] C-Motor: Clearing RAM Standby List...",
            "success": "[+] C-Motor executed successfully! System is clean.",
            "launching": "[+] Launching Counter-Strike 2 with ideal parameters...",
            "ask_launch": "❓ Do you want to launch Counter-Strike 2 now? (Y/N): ",
            "exit": "Press Enter to exit..."
        },
        "ru": {
            "title": "ГИБРИДНЫЙ ОПТИМИЗАТОР CS 2 (Python + C)",
            "launch": "👉 СФОРМИРОВАННЫЕ ПАРАМЕТРЫ ЗАПУСКА:",
            "checking": "[...] Подготовка системы и закрытие фоновой CS2...",
            "call_c_gpu": "[...] Си-Мотор: Сбрасываю кэш шейдеров видеокарт...",
            "call_c_steam": "[...] Си-Мотор: Очищаю кэш шейдеров Steam (ID 730)...",
            "call_c_ram": "[...] Си-Мотор: Очищаю Standby List оперативной памяти...",
            "success": "[+] Си-Мотор отработал успешно! Система чиста.",
            "launching": "[+] Запускаю Counter-Strike 2 с идеальными параметрами...",
            "ask_launch": "❓ Запустить Counter-Strike 2 прямо сейчас? (Y/N): ",
            "exit": "Нажмите Enter для выхода..."
        }
    }

    lang = "ru"
    for arg in sys.argv:
        if arg.startswith("--lang="):
            lang = arg.split("=")[1]

    if not is_admin() and not any(arg.startswith("--lang=") for arg in sys.argv):
        os.system('cls' if os.name == 'nt' else 'clear')
        print("============================================================")
        print("         Select language / Выберите язык:")
        print("============================================================")
        print("  1 - English")
        print("  2 - Русский")
        print("============================================================")
        choice = input("👉 ")
        lang = "en" if choice == "1" else "ru"

    if not is_admin():
        args = [f'"{arg}"' for arg in sys.argv] + [f"--lang={lang}"]
        ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, " ".join(args), None, 1)
        sys.exit(0)

    txt = strings_db[lang]

    os.system('cls' if os.name == 'nt' else 'clear')
    print("=" * 60)
    print(f"         {txt['title']}")
    print("=" * 60)

    cores = multiprocessing.cpu_count()
    threads_for_cs2 = cores // 2 if cores > 4 else cores
    launch_options = f"-high -nojoy -fullscreen -threads {threads_for_cs2} +fps_max 0"

    print(f"{txt['launch']}\n\033[92m{launch_options}\033[0m\n")
    print("-" * 60)

    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Software\Valve\Steam")
        steam_path, _ = winreg.QueryValueEx(key, "SteamPath")
        winreg.CloseKey(key)
        
        cs2_path = os.path.normpath(f"{steam_path}/steamapps/common/Counter-Strike 2")
        if os.path.exists(cs2_path):
            os.system(f'powershell -Command "Add-MpPreference -ExclusionPath \'{cs2_path}\'" >nul 2>&1')
    except:
        pass

    print(txt['checking'])
    os.system("taskkill /f /im cs2.exe >nul 2>&1")

    if getattr(sys, 'frozen', False):
        base_path = sys._MEIPASS 
    else:
        base_path = os.path.dirname(__file__) 

    try:
        dll_path = os.path.join(base_path, 'cleaner.dll')
        c_library = ctypes.CDLL(dll_path)
        
        print(txt['call_c_gpu'])
        c_library.clear_gpu_cache()
        
        print(txt['call_c_steam'])
        c_library.clear_steam_shader_cache()
        
        print(txt['call_c_ram'])
        c_library.clear_ram_standby_list()
        
        print(f"\n{txt['success']}")
    except Exception as e:
        print(f"\n[-] Error/Ошибка: {e}")

    print("-" * 60)

    ask = input(txt['ask_launch'].strip().lower())
    if ask in ['y', 'yes', 'д', 'да', '']:
        print(txt['launching'])
        steam_launch = f"start steam://run/730// {launch_options}"
        os.system(steam_launch)

    print("=" * 60)
    input(f"\n{txt['exit']}")

if __name__ == "__main__":
    main()
