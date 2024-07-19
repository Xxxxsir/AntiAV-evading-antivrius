# AntiAV

A PoC implementation for an evasion technique to hiding the target process.Using Hooking techniques and memory separation techniques to achieve evasion of shellcode detection, tested to bypass antivirus software such as ESET, 360, Huorong, and others.

# Description

This code implementation has various encrypt methods，you can choose one you like👀(here I recommand use customized xor)

the bulit-in encrypt methods are :

🟢RC4
🟢SystemFunction033

# components
• EnCrypt and DeCrypt functions:here u can define your own encoding method

• FileCrypt:output the encoded codeshell file

• Main program:This is where you would write your agent code,loading the encrypted shellcode and it's the portion of the code that will make use of AntiAv

# Compile
 i would recommend that use the visual studio 2022 with the specific settings,which i will not list in the doc
 
