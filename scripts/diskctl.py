#!/usr/bin/env python3



import os
import sys
import argparse

from gpt_image.disk import Disk
from gpt_image.partition import Partition
from gpt_image.partition import PartitionType


p = argparse.ArgumentParser()

p.add_argument("-c", "--create", action="store_true")
p.add_argument("-n", "--name", action="store")
p.add_argument("-s", "--size", action="store")

args = p.parse_args()




class DiskUtil:
    def __init__(self):
        self.disk_name = None
        self.disk_size = 0
        self.disk_handle = None

    def disk_open(self, name = None):
        if name == None:
            return

        # TODO:
        # Overwrite existing disk (if needed)
        self.disk_name = name
        self.disk_handle = Disk(self.disk_name)

    def disk_create(self, size = 0):
        if size == 0:
            return

        if self.disk_handle == None:
            return

        self.disk_size = size
        self.disk_handle.create(size)

    def disk_commit(self):
        if self.disk_handle == None:
            return

        self.disk_handle.commit()



def main():
    disk = DiskUtil()

    if args.create:
        if args.name == None:
            print("Invalid disk name!")
            sys.exit(-1)

        if args.size == 0:
            print("Invalid disk size!")
            sys.exit(-1)
        
        disk_size = int(args.size)

        disk.disk_open(args.name)
        disk.disk_create(disk_size)

    disk.disk_commit()
    sys.exit(0)


if __name__ == "__main__":
    main()
