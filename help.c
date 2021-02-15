/**
 * help.c
 * @author Ulyan Sobin
 */

const char *HELP_DOCUMENT =
"Command Format:\n"
"    smash [options] <file path> [<file path> ... ]\n\n"
"Options:\n"
"-------------------------------------------------------------------\n"
"Option |  Full    |  Description\n"
"-------+----------+------------------------------------------------\n"
"-h, -? |  --help  |  Display this document.\n"
"-c     |  --clean |  Clear the deleted files in the partition.\n"
"       |          |  Follow a directory path of a target partition.\n"
"-------------------------------------------------------------------\n\n"
"For example, if you want to delete \'a.txt\', try:\n"
"    smash a.txt\n\n";