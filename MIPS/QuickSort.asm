.data
fin: .asciiz "C:\\Users\\TanPhat\\Desktop\\MIPS\\input_sort.txt"
filenamewrite: .asciiz "C:\\Users\\TanPhat\\Desktop\\MIPS\\output_sort.txt"
	luutru: .space 4000
	bientam: .space 4000
	array: .word 0: 1000
	message: .space 40000
.text

main:
	la $t6,array
	#2<=n<=1000
# Open file for reading

	li   $v0, 13       # system call for open file
	la   $a0, fin      # input file name
	li   $a1, 0        # flag for reading
	li   $a2, 0        # mode is ignored
	syscall            # open a file 
	move $s0, $v0      # save the file descriptor 
# reading from file just opened

	li   $v0, 14       # system call for reading from file
	move $a0, $s0      # file descriptor 
	la   $a1, message   # address of buffer from which to read
	li   $a2,  40000  # hardcoded buffer length
	syscall            # read from file
################################################# Start read each number

	addi $t1,$0,0		#len=0
	la $t0,message   	# load message into t0

loop:
	lb   $s0,0($t0)  
	beqz $s0,done		#if message[i]==0
	addi $t0,$t0,1	
	addi $t1,$t1,1		#len+=1
	j     loop

done:
	sub $t0,$t0,$t1		#reset t0
	subi $t2,$t1,1		#t2=len-1
	add $s1,$0,$0		#sum=0	
	addi $s3,$0,1		#p=1
	addi $s5,$0,10		#x=10

	addi $t3,$0,32		# space
	addi $t7,$0,13		#xuongdong
	addi $s6,$0,10		# dongmoi
Start_read:
	move $s1,$0			#reset sum=0	
	addi $s3,$0,1		#reset p=1
	addi $s5,$0,10		#reset x=10
While_split:

	add $t0,$t0,$t2   	#t0=t0+t2
	lb $s2,0($t0)		#s2= message[t0]
	beq $s2,$t3,cach	#khi gap cach
	beq $s2,$s6,dongmoi	#khi gap dongmoi
	beq $s2,$t7,xuongdong	#khi gap xuongdong
	
 	beqz $s2, end_split		#khi het chuoi     #new
	
	addi $s2, $s2, -48	#s2=s2-48
	mult $s2,$s3		
	mflo $s4		#s4=s2*p
	add  $s1,$s1,$s4	#sum=sum+s4
	sub $t0,$t0,$t2		#t0=t0-t2

	
	addi $t2,$t2,-1		#t2=t2-1
	
	mult $s3,$s5		
	mflo $s4		#s4=p*10
	add $s3,$0,$s4		#p=s4

	
	j While_split
cach:
	sw  $s1,0($t6)   #save $s1 into array	
	
	addi $t6,$t6,4     #$t6=$t6+4

	sub $t0,$t0,$t2		#t0=t0-t2
	addi $t2,$t2,-1		#t2=t2-1
	j Start_read
xuongdong:
	sub $t0,$t0,$t2		#t0=t0-t2
	addi $t2,$t2,-1		#t2=t2-1
	j Start_read
dongmoi:
	
	sw $s1,0($t6)   #save $v0 into array	
	


	sub $t0,$t0,$t2		#t0=t0-t2
	addi $t2,$t2,-1		#t2=t2-1
	j Start_read
end_split:


	move $s7,$s1

# Close the file 

li   $v0, 16       # system call for close file
move $a0, $s6      # file descriptor to close
syscall            # close file	
	 
	j Start

partition:
##a0 : array
#a1 : low
#a2 : high
#s0 : i
#s1 : j		
#s2 : temp		
#s3 :pivot
#s4 : array access
#t0 : a[j] ,a[low]
#v1 : return j
	addi $sp, $sp, -16	#Make room for 5

	sw $a0, 0($sp)		#store a0
	sw $a1, 4($sp)		#store a1
	sw $a2, 8($sp)		#store a2
	sw $ra, 12($sp)		#store return address

	move $s0, $a1		#i=low
	move $s1, $a2		#j=high

	sll $s4, $a1, 2		# s4 = 4*low
	add $s4, $a0, $s4	# s4 = arr + 4*low
	lw $s3, 0($s4)		# pivot = arr[low] //pivot

Loop1_0:

Loop1_1:	
	addi $s0,$s0,1		#i=i+1

	sll $s4, $s0, 2		#s4 = i*4
	add $s4,$a0,$s4		#s4 = arr + 4i
	lw $t7, 0($s4)		#t7 = arr[i]

	slt $s6,$s3,$t7		#if a[i]<=pivot ==> jump Loop1_1
	beq $s6,$0,Loop1_1
	
Loop1_2:
	addi $s1,$s1,-1		#j=j-1

	sll $s4, $s1, 2		#s4 = j*4
	add $s4,$a0,$s4		#s4 = arr + 4j
	lw $t8, 0($s4)		#t8 = arr[j]

	slt $s6,$s3,$t8		#if a[j]>pivot ==> jump Loop1_2
	bne $s6,$0,Loop1_2
	
	slt $s6,$s0,$s1		#if i >=j
	beq $s6,$0,Endifpar
#swap
	sll $s4, $s0, 2		#s4 = i*4
	add $s4,$a0,$s4		#s4 = arr + 4i
	lw $s2, 0($s4)		#temp = arr[i]
	
	sll $s4, $s1, 2		#s4 = j*4
	add $s4,$a0,$s4		#s4 = arr + 4j
	lw $t0, 0($s4)		#t0 = arr[j]

	sll $s4, $s0, 2		#s4 = i*4
	add $s4,$a0,$s4		#s4 = arr + 4i
	sw $t0,0($s4)		#a[i]=a[j]

	sll $s4, $s1, 2		#s4 = j*4
	add $s4,$a0,$s4		#s4 = arr + 4j
	sw $s2,0($s4)		#a[j]=temp	

	j Loop1_0

Endifpar:
	sll $s4, $s1, 2		#s4 = j*4
	add $s4,$a0,$s4		#s4 = arr + 4j
	lw $s2, 0($s4)		#temp = arr[j]	

	sll $s4, $a1, 2		#s4 = low*4
	add $s4,$a0,$s4		#s4 = arr + 4*low
	lw $t0, 0($s4)		#t0 = arr[low]

	sll $s4, $s1, 2		#s4 = j*4
	add $s4,$a0,$s4		#s4 = arr + 4j
	sw $t0,0($s4)		#a[j]=a[low]

	sll $s4, $a1, 2		#s4 = low*4
	add $s4,$a0,$s4		#s4 = arr + 4*low
	sw $s2,0($s4)		#a[low]=temp

	add $v1, $0, $s1	#v1 = j return j;

	lw $ra, 12($sp)		#return address
	addi $sp, $sp, 16		#restore the stack
	jr $ra			#junp back to the caller		

########################################################
quicksort:				
# t8=high
# s5=v1
	addi $sp, $sp, -16		# Make room for 4

	sw $a0, 0($sp)		# a0
	sw $a1, 4($sp)		# low
	sw $a2, 8($sp)		# high
	sw $ra, 12($sp)		# return address

	move $t8, $a2		#saving high in t8

	slt $t1, $a1, $t8		# t1=1 if low < high, else 0
	beq $t1, $zero, endif		# if low >= high, endif

	jal partition		# call partition 
	move $s5, $v1		# pivot, s5= v1

	lw $a1, 4($sp)		#a1 = low
	add $a2, $s5,$0		#a2 = pi
	jal quicksort		#call quicksort

	addi $a1, $s5, 1	#a1 = pi + 1
	lw $a2, 8($sp)		#a2 = high
	jal quicksort		#call quicksort
#########################################################
 endif:

 	lw $a0, 0($sp)			#restore a0
 	lw $a1, 4($sp)			#restore a1
 	lw $a2, 8($sp)			#restore a2
 	lw $ra, 12($sp)			#restore return address
 	addi $sp, $sp, 16		#restore the stack
 	jr $ra				#return to caller
##########################################################
Start:
	la $t2, array # Moves the address of array into register $t0.
	addi $a0, $t2, 0 # array.
	addi $a1, $0, 0 # low = 0
	addi $a2, $s7,0 # high = n
	jal quicksort # Call quick sort
	j Cout	

Cout:

##################################################################################	
#open file
	addi $v0,$0,13	#open file: 13
	la $a0,filenamewrite	#get the filenamewrite
	addi $a1,$0,1	#flag=0 :read, flag=1 :write
	syscall		
	addi $s1,$v0,0

	addi $t1,$0,0
#	addi $s7,$0,3
	la $t3,luutru
		
	la $t2,array	
nhaylenday:	
	la $t6,bientam
	beq $t1 $s7 Write     #if $t2>=$s7
	lw $s3,0($t2)
	
	move $s2,$0		#count ki tu trong bientam
	addi $t4,$0,10	#t4: so de chia/nhan 10
Daoso:
	div $s3,$t4		#so/10
	mflo $t7		#thuong
	mfhi $t5		#du

	addi $t5,$t5,48	#du=du+48
	sb $t5,0($t6)	#luu du vao bientam	
	addi $t6,$t6,1	#bientam=bientam+1
	addi $s2,$s2,1	#count+=1

	add $s3,$0,$t7	#so=thuong		
	bgtz $s3,Daoso

phanluutru:	
	sub $t6,$t6,$s2	#reset bientam
	subi $t4,$s2,1	#t4=len-1
	
Startluutru:
	add $t6,$t6,$t4	#t6=t6+t4
	lb $t7,0($t6)
	sb $t7,0($t3)
	addi $t3,$t3,1
	sub $t6,$t6,$t4
	addi $t4,$t4,-1
	blt $t4,$0,nhay
	j Startluutru

nhay:
	addi $t5,$0,32	# space
	sb $t5,0($t3)
	addi $t3,$t3,1
	addi $t1,$t1,1
	addi $t2,$t2,4
	sub $t6,$t6,$t6
	j nhaylenday

Write:
#Writefile
	addi $v0,$0,15
	add $a0,$s1,$0
	la $a1,luutru
	la $a2,4000
	syscall

#close
	addi $v0,$0,16
	add $a0,$s1,0
	syscall
