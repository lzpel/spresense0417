Device Driver->Board Specific Driver
Device Driver->Audio Device Support
Device Driver->CXD56 SDK Audio Driver

両者は別物で/dev/audio/pcm0を生やすには前者が必要
+AUDIO_CXD56=y
+CXD56_AUDIO=y

menuconfigのどの設定がAUDIO_CXD56を生やすのかは調査が必要．
あるいは存在しないのかもしれない．
defconfigを主、menuconfigを従としてdefconfigを直接設定する

System Type>CXD56xx Package Configuration>NX Audio Driver Support>CXD56 NuttX audio driver
が