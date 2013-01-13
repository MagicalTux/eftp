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

# dir

This table contains the directory structure. Directory #0 is the root

* dir_id
* parent_dir_id
* name
* chmod
* created (int)
* modified (int)
* deleted (int, NULL)
* impl (int, NULL)

# file

* file_id
* dir_id
* name
* chmod
* size
* created (int)
* modified (int)
* deleted (int, NULL)
* impl (int, NULL)

# file_block

In this table, file_id+offset form an unique key.

* block_id
* file_id
* offset
* block_hash
* modified

