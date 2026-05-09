import os
import shutil

# 获取当前脚本所在目录
print(f'=' * 30, 'setup_tft_espi.py', '=' * 30)
print(f'Current working directory: {os.getcwd()}')
# 定义源文件和目标路径
src_header = os.path.join("assets", 'esp32_ST7789.h')
dst_header = os.path.join('.pio', 'libdeps', 'esp32dev', 'TFT_eSPI', 'esp32_ST7789.h')

src_user_setup = os.path.join("assets", 'User_Setup_Select.h')
dst_user_setup = os.path.join('.pio', 'libdeps', 'esp32dev', 'TFT_eSPI', 'User_Setup_Select.h')

src_lvconf_setup = os.path.join("assets", 'lv_conf.h')
dst_lvconf_setup = os.path.join('.pio', 'libdeps', 'esp32dev', 'lv_conf.h')
# 强制复制函数
def force_copy(src, dst):
    if os.path.exists(dst):
        print(f'Removing existing file: {dst}')
        os.remove(dst)
    print(f'Copying {src} to {dst}')
    shutil.copy(src, dst)

# 复制函数
def no_update_copy(src, dst):
    if not os.path.exists(dst):
        print(f'Copying {src} to {dst}')
        shutil.copy(src, dst)
    else:
        print(f'{dst} exists, skipping copy')

# 执行复制
force_copy(src_header, dst_header)
force_copy(src_user_setup, dst_user_setup)
# no_update_copy(src_lvconf_setup, dst_lvconf_setup)

print(f'=' * 30, 'setup_tft_espi.py', '=' * 30)