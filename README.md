# AntiAV

A PoC implementation for an evasion technique to hiding the target process.Using Hooking techniques and memory separation techniques to achieve evasion of shellcode detection, tested to bypass antivirus software such as ESET, 360, Huorong, and others.

# Description

This code implementation has various encrypt methods，you can choose one you like👀(here I recommand use customized xor)

the bulit-in encrypt methods are :

🟢RC4
🟢SystemFunction033
🟢A simple eg xor

# components
• EnCrypt and DeCrypt functions:here u can define your own encoding method

• FileCrypt:output the encoded codeshell file

• Main program:This is where you would write your agent code,loading the encrypted shellcode and it's the portion of the code that will make use of AntiAv

# Compile
 I would recommend that use the visual studio 2022 with the specific settings:

 • Modify and optimize for size minimization with /O1.

 • Choose multi-threaded code generation with /MT. There are compatibility issues with using /MD, so it is generally not used. 

 • Set manifest generation to No, as not using a manifest results in lower false positives for virus detection.
 
# Usage
first,u are supposed to use the encrypt func and file convert func to convert your original PE file or shell code to encoded one.then you modify the encoded file path in the main.cpp,which uses the corresponding decrypt method.

