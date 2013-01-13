# Preface

Clients and server have a database that contain data. Both side share the same
data structure.

The impl column is used to store the stamp at which the file was last updated
on local filesystem. It is only used by clients.

Entries from tables dir and file are kept in database even after being deleted
so it is possible to re-create them. If a client receives an update for a file
which modified stamp is higher than local deleted stamp, it means the file is
to be re-instanciated.

Deleted files have their size trimmed to zero, which means that all entries
from the file_block table for this file are to be deleted.

# inode

This table contains the tree structure. Inode #0 is the root.

* inode_id
* parent_inode_id
* name
* type (char(1), "d" or "f")
* chmod
* size
* created (bigint)
* modified (bigint)
* deleted (bigint, NULL)
* impl (bigint, NULL)

# block

In this table, inode_id+offset form an unique key.

* block_id
* inode_id
* offset
* block_hash
* modified

