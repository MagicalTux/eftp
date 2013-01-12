# eftp

This software comes with a client and a server.

The server stores files and allows clients to retrieve data.

The client retrieves data, stores it locally, detects changes and uploads
changes to the server.

This works kinda like Dropbox, but different to suit my own needs. If you
happen to have the same needs, feel free to use this piece of software and
improve it maybe.

# Storage on server

The server will just store blocks of a pre-defined size sorted by their hash
(by default SHA1) in a compressed way (files are compressed by the client).
The default implementation has a 2MB block size.

Note that if you recompile the system with a different block size, the data on
the server will become unusable, and needs to be deleted.

A separate database contains the hierarchy of all files & directories with
attributes and latest change date, and list of blocks for each file.

Database is in SQLite format.

The database itself is "kinda" replicated between the server and clients.

