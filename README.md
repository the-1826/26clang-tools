# 1826s tooleys 

A few tools I've made during my GTA LCS modding journey. They have a narrow scope mostly.

## Language Chronicles

Language-switch tool, useful if you want to switch from one language to another in GTA LCS when using a decompiled EBOOT.BIN file.

### How to use
For switching the language, use:

`language.exe <InputFile> <TargetGXTName>`

Allowed target .gxt names:

* ENGLISH.GXT
* GERMAN.GXT
* FRENCH.GXT
* ITALIAN.GXT
* SPANISH.GXT

### Example:

`language.exe lcs.iso german.gxt`

This will make the lcs.iso game use the german.gxt file in all cases.

## LCS-M Russian .gxt Encoder 

Language-encoding tool, useful if you want to convert Russian PSP/PS2 GTA LCS .gxt format (with Dageron encoding) to the mobile format.

### How to use
For switching the language, use:

`encoder.exe <InputFile>`

### Example:

`encoder.exe russian.gxt`

This will generate a result.gxt file for the mobile version of the game in the same folder.

## VagMemeInsert

Tool made for randomising names of the .vag files with a set of predefined strings. Could be useful if you want to put copyrights inside these.

### How to use
First, store a set of strings in 'memeinsert.cfg' file, you can find an example of that in the repository files. 

Use:

`vagmemeinsert.exe <InputFile1> <InputFile2> <InputFile3>...` (unlimited amout of files supported)

### Example:

`vagmemeinsert.exe audio1.vag audio2.vag`

This will change the header of these vag files completely changing the names section with random predefined names.

## NamePicker
Audio tool, useful if you want to pick names for audios you will put into SFXn_PSP.RAW/SFXn_PS2.RAW archives. Put contents of the archives in 'sourcefiles' folder located in the same directory with the NamePicker .exe. Then drag'n'drop .vag file you want to use in the game on the NamePicker executable: program will automaticaly find the most suitable candidate for the replacement, adjust your file weight, rename it and remove the replaceable file from the 'sourcefiles' folder.

### How to use
First, store a set of .vag replacement candidates in 'sourcefiles' folder located in the same directory with the namepicker.exe, you can find an example of that in the repository files. 

Use:

`namepicker.exe <InputFile1> <InputFile2> <InputFile3>...` (unlimited amout of files supported)

### Example:

`namepicker.exe ELEPHANT1.vag ELEPHANT2.vag ELEPHANT3.vag ELEPHANT4.vag`

This will adjust the file weight, rename it and remove the replaceable file from the sourcefiles folder. Information regarding the replacement will be stored in the log file which will be stored in one folder with the NamePicker executable file.
