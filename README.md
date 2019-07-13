# Torrent--

It is a miniBitTorrent file sharing system(peer to peer file sharing).
code is written with respect to linux file system and path hierarchy.

Features:

  ❖ Client
    ➢ None of the command is blocking command - Use of multithreading
    ➢ Share : Create mtorrent file - share details with tracker
    ➢ Get : peer info from tracker - receive chunks from multiple peers
    ➢ Remove : stop sharing - delete mtorrent file
    ➢ Close : remove entries from seederlist for this client.
    ➢ Show downloads : list of file with status ( downloaded/downloading )
    ➢ Seed file as soon as starts downloading
    ➢ Client comes back online - share info of all existing mtorrent with tracker
    ➢ Maintain log file
    ➢ Error handling and validations
    ➢ Absolute and relative paths support, name with spaces are allowed
    
  ❖ Server
    ➢ 4 type of requests : share, get, remove, close
    ➢ Tracker synchronization
    ➢ Maintain seederlist ( persistent storage )
    ➢ Maintain server logs
