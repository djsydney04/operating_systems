# Memory management: study notes

## Addresses and paging

- A logical (virtual) address is the address a program uses. A physical address identifies a location in main memory.
- Memory is byte-addressed in these examples. A page is a fixed-size block of virtual memory; a frame is a block of physical memory of the same size.
- A logical address contains a page number and an offset. The page number identifies the page; the offset identifies a byte within it.
- A physical address contains a frame number and the same offset. The page table maps the page number to a frame number.
- If there are 2^n possible values, n bits can identify each value.

## Example: address sizes

Given 256 pages, a 4-KB page size, and 64 frames:

- 256 pages = 2^8 pages: 8 bits for the page number.
- 4 KB = 4,096 bytes = 2^12 bytes: 12 bits for the offset.
- Logical address: 8 + 12 = **20 bits**.
- 64 frames = 2^6 frames: 6 bits for the frame number.
- Physical address: 6 + 12 = **18 bits**.

## Revisit

- [ ] Practice the difference between a page number and a frame number, and how the page table maps one to the other.
- [ ] Practice how an offset identifies a byte in a page and why it stays the same when a page is mapped to a frame.
- [ ] Practice converting between powers of two, numbers of possible positions, and bits.
