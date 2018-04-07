# LuaTools

制作人：Blacat Recycler

## 应用介绍

本小程序是为了学习目的开发，针对Cocos2dx-Lua开发的安卓游戏反编译设计。用于拆包得到的Lua文件加解密，仅仅为了获取源码学习开发。禁止用于修改游戏数据进行作弊

## 使用方法

在控制台中运行，输入以下

|命令格式|作用|
|:--|:---|
|D(d) [fileName] \[sign] \[key]|根据输入的Sign和Key解密文件，解密文件为原文件名\+\'.lua\'|
|B(b) [fileName] \[sign] \[key]|根据输入的Sign和Key加密文件，加密文件为原文件名去除\'.lua\'|