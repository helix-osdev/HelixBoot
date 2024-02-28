#!/usr/bin/env python3



import os
import sys
import argparse

from gpt_image.disk import Disk
from gpt_image.partition import Partition
from gpt_image.partition import PartitionType




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

    disk.disk_open("test")
    disk.disk_create(16 * 1024 * 1024)
    disk.disk_commit()

    sys.exit(0)


if __name__ == "__main__":
    main()
