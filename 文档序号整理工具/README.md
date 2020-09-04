# 文档序号整理
1.最新版本需要使用如下方法做adb remount

    Ubuntu系统
    1、在开发者选项里开启OEM unlocking(如果OEM unlocking显示灰色，则表示设备已经处于unlock状态，可以直接跳到第6步操作)
    2、adb reboot bootloader
    3、sudo fastboot flashing unlock(如果fastboot失败，可用Android源码out/host/linux-x86/bin/fastboot)
    4、按音量上键，提示unlock pass
    5、sudo fastboot reboot
    6、adb root
    7、adb disable-verity
    8、adb reboot
    9、adb root
    10、adb remount

    adb reboot bootloader
    sudo fastboot flashing unlock
    sudo fastboot reboot
    sleep 41s
    adb root
    adb disable-verity
    adb reboot
    sleep 45s
    adb root
    adb remount

	
2.V830/V730 MTK6762 Q：

    http://192.168.160.3/mediawiki/index.php/V830/V730_MTK6762_Q#userdebug.E7.89.88.E6.9C.ACremount.E7.9A.84.E5.91.BD.E4.BB.A4


以上是例子，格式必须是以 1. 或者 2.之类的开头，内容以Tab后面接内容，可以随意插入想插入的位子，运行该程序会自动有序进行编号
