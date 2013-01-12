# Preface

Clients and server have a database that contain data. Both side share the same
data structure.

The impl column is used to store the stamp at which the file was last updated
on local filesystem. It is only used by clients.

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

