.data
    xuat: .asciiz "Nhap n: "
    cachra: .asciiz "  "
    tongla: .asciiz "\nTong cac phan tu la:"
    somax: .asciiz "\nGia tri lon nhat la:  "
    songuyento: .asciiz "\nSo nguyen to: "
    timx: .asciiz "\nNhap x: "
    timthayx: .asciiz "\nTim thay o vi tri thu "
    khongtimthayx: .asciiz "\nKhong tim thay "

    menu: .asciiz "\nMENU\n"
    chon1: .asciiz "1.Xuat ra cac phan tu\n"
    chon2: .asciiz "2.Tinh tong cac phan tu\n"
    chon3: .asciiz "3.Liet ke cac phan tu la so nguyen to\n"
    chon4: .asciiz "4.Gia tri lon nhat\n"
    chon5: .asciiz "5.Tim phan tu co gia tri x\n"
    chon6: .asciiz "6.Thoat\n"
    chon7: .asciiz "\nNhap lua chon:"

.text
j main
#################################################
Cout:
addi $t2,$0,0   #i=0
add $s1,$s1,$s2  #reset $s1=0
addi $t5,$0,0   #bien dem de tru
Loop:
    beq $t2 $s0 end     #if $t2>=$s0

     sll $t4,$t2,2
     add $t4,$s1,$t4
     lw $t3, 0($t4)   #save $v0 into $t4

     addi $v0,$0,1
     add $a0,$0,$t3
     syscall

     addi $v0,$0,4
     la $a0,cachra
     syscall

     addi $t5,$t5,4
    addi $t2 $t2 1   #$t2=$t2+1
  
    j Loop

end:
 	add $s1,$s1,$t5
	j Start

###################################################
TinhTong:
addi $t2,$0,0   #i=0
add $s1,$s1,$s2
addi $t5,$0,0   #sum=0
addi $t6,$0,0
Loop_Sum:
    beq $t2 $s0 end_Sum     #if $t2>=$s0

     sll $t4,$t2,2
     add $t4,$s1,$t4
     lw $t3, 0($t4)   #load $v0 into $t4

     add $t5,$t5,$t3

     addi $t6,$t6,4

    addi $t2 $t2 1   #$t2=$t2+1

    j Loop_Sum

end_Sum:
	
	addi $v0,$0,4
	la $a0,tongla
	syscall
	addi $v0,$0,1
	add $a0,$0,$t5
	syscall
	add $s1,$s1,$t6
	j Start
#################################################
LonNhat:
addi $t2,$0,0   #i=0
add $s1,$s1,$s2  #reset $s1=0
sll $t4,$t2,2   #y=i*4 -->y=0
add $t4,$s1,$t4   #y=0+y   ->y=0
lw $t3,0($t4)     

add $t5,$0,$t3   #max=x[0]
addi $t4,$0,0
addi $t6,$0,0
Loop_Max:
      beq $t2 $s0 end_Max     #if $t2>=$s0

     sll $t4,$t2,2    #$t4=$t2*4
     add $t4,$s1,$t4  #$t4=$t4+0
     lw $t3, 0($t4)   #save $t3 into $t4

     jal continue

    addi $t6,$t6,4
    addi $t2 $t2 1   #$t2=$t2+1
    j Loop_Max

continue:

     slt $t7,$t5,$t3    
     bne $t7,$0,gan
     jr $ra
gan:
   add $t5,$0,$t3

   jr $ra


end_Max:
    addi $v0,$0,4
     la   $a0,somax
    syscall

    addi $v0,$0,1
    add $a0,$0,$t5
    syscall

    add $s1,$s1,$t6
    j Start
#################################################
TimKiem:
addi $t2,$0,0   #i=0

add $s1,$s1,$s2


	addi $v0,$0,4
	la $a0,timx
	syscall

	addi $v0,$0,5
	syscall
	add $t1,$0,$v0     #$t1=x
Loop_Found:
    beq $t2 $s0 end_Found     #if $t2>=$s0

     sll $t4,$t2,2    #$t4=$t2*4
     add $t4,$s1,$t4  #$t4=$t4+0
     lw $t3, 0($t4)   #save $t3 into $t4


     beq $t1,$t3,ketluan   #x==a[i]

    addi $t2 $t2 1   #$t2=$t2+1

    j Loop_Found

ketluan:
   addi $v0,$0,4
     la   $a0,timthayx
    syscall
    
   addi $v0,$0,1
   add $a0,$0,$t2
   syscall

   add $s1,$s1,$s3
    j Start

end_Found :

    addi $v0,$0,4
     la   $a0,khongtimthayx
    syscall

    add $s1,$s1,$s3
    j Start
#################################################
LietkeNguyenTo:
addi $t2,$0,0   #i=0
add $s1,$s1,$s2

	addi $v0,$0,4
	la   $a0,songuyento
	syscall
Loop_SNT:
    beq $t2 $s0 end_SNT     #if $t2>=$t0

     sll $t4,$t2,2    #$t4=$t2*4
     add $t4,$s1,$t4  #$t4=$t4+0
     lw $t3, 0($t4)   #save $t3 into $t4

     jal Check_SNT
   
    addi $t2 $t2 1   #$t2=$t2+1

    j Loop_SNT

Check_SNT:
         
     
     blt $t3,1,NotPrime  # if s3<1 ->jump Notprime
     beq $t3,1,NotPrime  # if s3=1 ->jump Notprime
     beq $t3,2,IsPrime   # if s3=2 ->jump Isprime
     addi $t1,$0,2 #j=2

while_SNT:
	bge $t1,$t3,IsPrime  #if j>=s3  ->goto exit
	div $t3,$t1 #$s3/j
	mfhi $t4 #so du
	beq $t4,$0,NotPrime
	

	addi $t1,$t1,1   #j=j+1
	
	j while_SNT   	#goto while_SNT
NotPrime:
     jr $ra
IsPrime:
    addi $v0,$0,1
    add $a0,$0,$t3
    syscall

    addi $v0,$0,4
    la   $a0,cachra
    syscall
    jr $ra

end_SNT :

   add $s1,$s1,$s3
    j Start
###############################################################
Thoat:
	addi $v0,$0,10	#exit
	syscall

main:

Loop_n:
	addi $v0,$0,4
	la   $a0,xuat   #cout<<xuat
	syscall

	addi $v0,$0,5
	syscall
	add $s0,$0,$v0	#$s0=n

  	slt $t1,$0,$s0
	beq $t1,$0,Loop_n	#if n<=0 tiep tuc


sll $t1,$s0,2    #$t1=$s0*4

add $v0,$0,9
add $a0,$0,$t1
syscall

add $s1,$0,$v0	#convert $s0 ==$s1

addi $t5,$0,0   	#i=1
addi $s3,$0,0	#bien $s1 de = $s1
addi $s2,$0,0	#bien $s2 de tru
Cin:
     bge $t5 $s0  Start	#if i>=n  ->jump Start
    # read in and store int
    li $v0 5
    syscall
    sw $v0 0($s1)   #save $v0 into $s1
    
    addi $t5 $t5 1   #$t5=$t5+1
    addi $s1 $s1 4   #$s1=$s1+4
    subi $s2,$s2,4   #$s2=$s2-4
    addi $s3,$s3,4   #$s3=$s3+4
    j Cin
#################################################
Start:
#Phan menu
addi $v0,$0,4
la $a0,menu
syscall

addi $v0,$0,4
la $a0,chon1
syscall

addi $v0,$0,4
la $a0,chon2
syscall

addi $v0,$0,4
la $a0,chon3
syscall

addi $v0,$0,4
la $a0,chon4
syscall

addi $v0,$0,4
la $a0,chon5
syscall

addi $v0,$0,4
la $a0,chon6
syscall
addi $t1,$0,1
addi $t2,$0,2
addi $t3,$0,3
addi $t4,$0,4
addi $t5,$0,5
addi $t6,$0,6
While_menu:
	addi $v0,$0,4
	la $a0,chon7		#cout<<Chon7
	syscall

	addi $v0,$0,5
	syscall
	add $t7,$0,$v0     #cin>>choose
	
	beq $t7 $t1 Cout	#if choose==$t1
	beq $t7 $t2 TinhTong	#if choose==$t2
	beq $t7 $t3 LietkeNguyenTo#if choose==$t3
	beq $t7 $t4 LonNhat	#if choose==$t4
	beq $t7 $t5 TimKiem	#if choose==$t5
	beq $t7 $t6 Thoat	#if choose==$t6

	slt $t0,$t7,$t1	#if choose <$t1
	bne $t0,$0,While_menu
	
	slt $t0,$t6,$t7
	bne $t0,$0,While_menu	#if choose>$t6
