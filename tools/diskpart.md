[Make a read only USB stick](https://www.getusb.info/how-to-make-a-usb-read-only/)
```bash
diskpart
> list disk
> select disk 1
> attributes disk set readonly
> exit
```

