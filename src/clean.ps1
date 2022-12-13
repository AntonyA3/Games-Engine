$found_files = Get-ChildItem -Path . -Name -Recurse -Include '*.[do]'
$found_files += Get-ChildItem -Path . -Name -Recurse -Include '*.exe'

foreach ($file in $found_files) {
   rm $file
}
