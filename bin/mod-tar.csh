#!/bin/csh

#####################################################
#
# script will zip up manually edited source
# that were modifid during last 5 days(optional)
# all autogenerated files will be skippet
#
####################################################

./bin/clean.csh

set days_test = $1
if($days_test == "")then
    set days_test = 5
endif

set date_label=`date +"%Y-%m-%d"`
set host_label=`hostname`
set tar_name=../mods-$host_label-$date_label.tar.gz

echo "====================================================="

#tar -czvf $tar_name  `find . -mtime -$days_test \( -name "*.cpp" -or -name "*.h" -or -name "*.pro" -or -name "*.csh"  -or -name "*.bat" \) | grep -v __tmp`
tar -czvf $tar_name  `find . -mtime -5 \( -name "*.cpp" -or -name "*.h" -or -name "*.pro" -or -name "*.csh" -or -name "*.bat" \) | grep -v __tmp | grep -v "./src/gtask/tasklists/" | grep -v "./src/gtask/AUTOTEST/" | grep -v "./src/gtask/tasks/" | grep -v "./src/gmail/messages" | grep -v "./src/gmail/labels/" | grep -v "./src/gmail/threads"  | grep -v "./src/gmail/users" | grep -v "./src/gmail/history"| grep -v "./src/gmail/errors"| grep -v "./src/gmail/drafts"| grep -v "./src/gmail/attachments"|grep -v "./src/gmail/AUTOTEST"|grep -v "./src/gdrive/revisions"|grep -v "./src/gdrive/permissions"|grep -v "./src/gdrive/files"|grep -v "./src/gdrive/comments"|grep -v "./src/gdrive/about"|grep -v "./src/gdrive/AUTOTEST"|grep -v "./src/gcontact/contacts"|grep -v "./src/gcontact/AUTOTEST"`


echo "====================================================="
tar -tvf $tar_name |sort -nk 3 | awk '{printf("%3.1fK\t%s\t%s\n", $3/1024, $4, $6)}'
split -b 140000 $tar_name ../mseg
echo "====================================================="

echo "older then "$days_test "days.." `ls -lsh $tar_name | awk '{print $1}'`
