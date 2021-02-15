# Smash
Tool to delete file thoroughly. Anti-recovery tool.

You can use this tool to delete files from HDD/SDD or flash disk thoroughly. You can also use it to clean the files which has been removed by system but still recoverable.

## Command Tutorial

```bash
smash [options] <file path> [<file path> ... ]
```

### Options

|Option|Full|Description|
|-|-|-|
|-h, -?|--help|Display this document. |
|-c|--clean|Clear the deleted files in the partition. Follow a directory path of a target partition. |

### Typical commands

Delete a file thoroughly:
```bash
smash a.txt
```

Delete files thoroughly:
```bash
smash a.txt b.txt
```

Clean the partition of a directory path:
```bash
smash --clean ~
```
or
```bash
smash -c /home/user
```