F$Link	== 0		;Link to Module 
F$Load	== 1		;Load Module from File 
F$UnLink == 2		;Unlink Module 
F$Fork	== 3		;Start New Process 
F$Wait	== 4		;Wait for Child Process to Die 
F$Chain	== 5		;Chain Process to New Module 
F$Exit	== 6		;Terminate Process 
F$Mem	== 7		;Set Memory Size 
F$Send	== 8		;Send Signal to Process 
F$Icpt	== 9		;Set Signal Intercept 
F$Sleep	== 10		;Suspend Process 
F$SSpd	== 11		;Suspend Process 
F$ID	== 12		;Return Process ID 
F$SPrior == 13		;Set Process Priority 
F$SSWI	== 14		;Set Software Interrupt 
F$PErr	== 15		;Print Error 
F$PrsNam == 16		;Parse Pathlist Name 
F$CmpNam == 17		;Compare Two Names 
F$SchBit == 18		;Search Bit Map 
F$AllBit == 19		;Allocate in Bit Map 
F$DelBit == 20		;Deallocate in Bit Map 
F$Time	== 21		;Get Current Time 
F$STime == 22		;Set Current Time 
F$CRC	== 23		;Generate CRC 
F$GPrDsc == 24		;Get Process Descriptor copy 
F$GBlkMap == 25		;Get System Block Map copy 
F$GModDr == 26		;Get Module Directory copy 
F$CpyMem == 28		;Copy External Memory 
F$SUser	== 29		;Set User ID number 
F$UnLoad == 30		;Unlink Module by name 

F$SRqMem == 40		;System Memory Request 
F$SRtMem == 1		;System Memory Return 
F$IRQ	== 1		;Enter IRQ Polling Table 
F$IOQu	== 1		;Enter I/O Queue 
F$AProc == 1		;Enter Active Process Queue 
F$NProc == 1		;Start Next Process 
F$VModul == 1		;Validate Module 
F$Find64 == 1		;Find Process/Path Descriptor 
F$All64	== 1		;Allocate Process/Path Descriptor 
F$Ret64	== 1		;Return Process/Path Descriptor 
F$SSvc	== 1		;Service Request Table Initialization 
F$IODel	== 1		;Delete I/O Module 
F$SLink	== 1		;System Link 
F$Boot	== 1		;Bootstrap System 
F$BtMem	== 1		;Bootstrap Memory Request 
F$GProcP == 1		;Get Process ptr 
F$Move	== 1		;Move Data (low bound first) 
F$AllRAM == 1		;Allocate RAM blocks 
F$AllImg == 1		;Allocate Image RAM blocks 
F$DelImg == 1		;Deallocate Image RAM blocks 
F$SetImg == 1		;Set Process DAT Image 
F$FreeLB == 1		;Get Free Low Block 
F$FreeHB == 1		;Get Free High Block 
F$AllTsk == 1		;Allocate Process Task number 
F$DelTsk == 1		;Deallocate Process Task number 
F$SetTsk == 1		;Set Process Task DAT registers 
F$ResTsk == 1		;Reserve Task number 
F$RelTsk == 1		;Release Task number 
F$DATLog == 1		;Convert DAT Block/Offset to Logical 
F$DATTmp == 1		;Make temporary DAT image 
F$LDAXY	== 1		;Load A [X,[Y]] 
F$LDAXYP == 1		;Load A [X+,[Y]] 
F$LDDDXY == 1		;Load D [D+X,[Y]] 
F$LDABX	== 1		;Load A from 0,X in task B 
F$STABX	== 1		;Store A at 0,X in task B 
F$AllPrc == 1		;Allocate Process Descriptor 
F$DelPrc == 1		;Deallocate Process Descriptor 
F$ELink	== 1		;Link using Module Directory Entry 
F$FModul == 1		;Find Module Directory Entry 
F$MapBlk == 1		;Map Specific Block 
F$ClrBlk == 1		;Clear Specific Block 
F$DelRam == 1		;Deallocate RAM blocks 

I$Attach == 128  ;Attach I/O Device 
I$Detach == 129  ;Detach I/O Device 
I$Dup	== 130  ;Duplicate Path 
I$Create == 131  ;Create New File 
I$Open	== 132  ;Open Existing File 
I$MakDir == 133  ;Make Directory File 
I$ChgDir == 134  ;Change Default Directory 
I$Delete == 135  ;Delete File 
I$Seek	== 136  ;Change Current Position 
I$Read	== 137  ;Read Data 
I$Write	== 138  ;Write Data 
I$ReadLn == 139  ;Read Line of ASCII Data 
I$WritLn == 140  ;Write Line of ASCII Data 
I$GetStt == 141  ;Get Path Status 
I$SetStt == 142  ;Set Path Status 
I$Close	== 143  ;Close Path 
I$DeletX == 144  ;Delete from current exec dir 

SS.Opt	== 0  ;Read/Write PD Options 
SS.Ready == 1  ;Check for Device Ready 
SS.Size	== 2  ;Read/Write File Size 
SS.Reset == 3  ;Device Restore 
SS.WTrk	== 4  ;Device Write Track 
SS.Pos	== 5  ;Get File Current Position 
SS.EOF	== 6  ;Test for End of File 
SS.Link	== 7  ;Link to Status routines 
SS.ULink == 8  ;Unlink Status routines 
SS.Feed	== 9  ;issue form feed 
SS.Frz	== 10  ;Freeze DD_ information 
SS.Spt	== 11  ;Set DD_TKS to given value 
SS.SQD	== 12  ;Sequence down hard disk 
SS.DCmd	== 13  ;Send direct command to disk 
SS.DevNm == 14  ;Return Device name (32-bytes at [X]) 
SS.FD	== 15  ;Return File Descriptor (Y-bytes at [X]) 
SS.Ticks == 16  ;Set Lockout honor duration 
SS.Lock	== 17  ;Lock/Release record 
SS.DStat == 18  ;Return Display Status (CoCo) 
SS.Joy	== 19  ;Return Joystick Value (CoCo) 
SS.BlkRd == 20  ;Block Read 
SS.BlkWr == 21  ;Block Write 
SS.Reten == 22  ;Retension cycle 
SS.WFM	== 23  ;Write File Mark 
SS.RFM	== 24  ;Read past File Mark 
SS.ELog	== 25  ;Read Error Log 
SS.SSig	== 26  ;Send signal on data ready 
SS.Relea == 27  ;Release device 

E$PthFul == 136  ;Path Table full 
E$BPNum	== 137  ;Bad Path Number 
E$Poll	== 138  ;Polling Table Full 
E$BMode	== 139  ;Bad Mode 
E$DevOvf == 140  ;Device Table Overflow 
E$BMID	== 141  ;Bad Module ID 
E$DirFul == 142  ;Module Directory Full 
E$MemFul == 143  ;Process Memory Full 
E$UnkSvc == 144  ;Unknown Service Code 
E$ModBsy == 145  ;Module Busy 
E$BPAddr == 146  ;Bad Page Address 
E$EOF	== 147  ;End of File 

E$NES	== 149  ;Non-Existing Segment 
E$FNA	== 150  ;File Not Accesible 
E$BPNam == 151  ;Bad Path Name 
E$PNNF	== 152  ;Path Name Not Found 
E$SLF	== 153  ;Segment List Full 
E$CEF	== 154  ;Creating Existing File 
E$IBA	== 155  ;Illegal Block Address 

E$MNF	== 157  ;Module Not Found 

E$DelSP == 159  ;Deleting Stack Pointer memory 
E$IPrcID == 160  ;Illegal Process ID 

E$NoChld == 162  ;No Children 
E$ISWI	== 163  ;Illegal SWI code 
E$PrcAbt == 164  ;Process Aborted 
E$PrcFul == 165  ;Process Table Full 
E$IForkP == 166  ;Illegal Fork Parameter 
E$KwnMod == 167  ;Known Module 
E$BMCRC	== 168  ;Bad Module CRC 
E$USigP	== 169  ;Unprocessed Signal Pending 
E$NEMod	== 170  ;Non Existing Module 

E$BNam	== 171  ;Bad Name 
E$NoRAM	== 172  ;No Ram Available 
E$BPrcID == 173  ;Bad Process ID 
E$NoTask == 174  ;No available Task number 

E$Unit	== 176  ;Illegal Unit (drive) 
E$Sect	== 177  ;Bad SECTor number 
E$WP	== 178  ;Write Protect 
E$CRC	== 179  ;Bad Check Sum 
E$Read	== 180  ;Read Error 
E$Write	== 181  ;Write Error 
E$NotRdy == 182  ;Device Not Ready 
E$Seek	== 183  ;Seek Error 
E$Full	== 184  ;Media Full 
E$BTyp	== 185  ;Bad Type (incompatable) media 
E$DevBsy == 186  ;Device Busy 
E$DIDC	== 187  ;Disk ID Change 
E$Lock	== 188  ;Record is busy (locked out) 
E$Share	== 189  ;Non-sharable file busy 
E$DeadLk == 190  ;I/O Deadlock error 
