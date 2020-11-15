**Lab Results**

**Command**
```
sudo hdparm -T -t /dev/sda
```

**Output**
```
/dev/sda:
 Timing cached reads:   29122 MB in  1.99 seconds = 14644.73 MB/sec
 Timing buffered disk reads: 966 MB in  3.01 seconds = 321.36 MB/sec
```

---

**Command**
```
sudo hdparm -a /dev/sda
```

**Output**
```
/dev/sda:
 readahead     = 256 (on)
```

---

**Command**
```
sudo hdparm -c /dev/sda
```

**Output**
```
/dev/sda:
 IO_support    =  1 (32-bit)
```

---

**Command**
```
sudo hdparm -a /dev/sda
```

**Output**
```
/dev/sda:
 readahead     = 256 (on)
```

---

**Command**
```
sudo hdparm -g /dev/sda
```

**Output**
```
/dev/sda:
 geometry      = 9090/255/63, sectors = 146037888, start = 0
```

---

**Command**
```
sudo hdparm -I /dev/sda
```

**Output**
```
/dev/sda:

ATA device, with non-removable media
	Model Number:       VBOX HARDDISK                           
	Serial Number:      VBe1fc0db7-fb12535d 
	Firmware Revision:  1.0     
Standards:
	Used: ATA/ATAPI-6 published, ANSI INCITS 361-2002 
	Supported: 6 5 4 
Configuration:
	Logical		max	current
	cylinders	16383	16383
	heads		16	16
	sectors/track	63	63
	--
	CHS current addressable sectors:    16514064
	LBA    user addressable sectors:   146037888
	LBA48  user addressable sectors:   146037888
	Logical/Physical Sector size:           512 bytes
	device size with M = 1024*1024:       71307 MBytes
	device size with M = 1000*1000:       74771 MBytes (74 GB)
	cache/buffer size  = 256 KBytes (type=DualPortCache)
Capabilities:
	LBA, IORDY(cannot be disabled)
	Queue depth: 32
	Standby timer values: spec'd by Vendor, no device specific minimum
	R/W multiple sector transfer: Max = 128	Current = 128
	DMA: mdma0 mdma1 mdma2 udma0 udma1 udma2 udma3 udma4 udma5 *udma6 
	     Cycle time: min=120ns recommended=120ns
	PIO: pio0 pio1 pio2 pio3 pio4 
	     Cycle time: no flow control=120ns  IORDY flow control=120ns
Commands/features:
	Enabled	Supported:
	   *	Power Management feature set
	   *	Write cache
	   *	Look-ahead
	   *	48-bit Address feature set
	   *	Mandatory FLUSH_CACHE
	   *	FLUSH_CACHE_EXT
	   *	Gen2 signaling speed (3.0Gb/s)
	   *	Native Command Queueing (NCQ)
Checksum: correct
```

**Discussion Question**
Review the following files associated with block IO:
```
block/genhd.c
fs/partitions/check.c
block/ll_rw_blk.c
include/linux/bio.h
include/linux/blkdev.h
include/linux/genhd.h
block/elevator.c
```
Discuss what you found in these files. What is the purpose of the code in each file? How do they fit together to block IO?

+ **block/genhd.c**
  + Block I/O disk operations and multithreading
+ **fs/partitions/check.c**
  + Handles some partitioning logic
+ **block/ll_rw_blk.c**
  + Handles read/write requests to block devices
+ **include/linux/bio.h**
  + Contains Block I/O data movement functionality. Includes functions that check if the bio is full and split the bio if needed.
+ **include/linux/blkdev.h**
  + I think this might be more scheduling code.
+ **include/linux/genhd.h**
  + Handles code for block i/o partitioning. Also defines some device addresses.
+ **block/elevator.c**
  + Implements block device elevator I/O scheduling.

**References**

(2012). An Introduction to Linux Block I/O. Retreived from https://researcher.watson.ibm.com/researcher/files/il-AVISHAY/01-block_io-v1.3.pdf.

(2020). bootlin. Elixir Cross Referencer. Retreived from https://elixir.bootlin.com/linux/.