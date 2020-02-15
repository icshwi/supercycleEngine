# Extension managment
* code --list-extensions >> vs_code_extensions_list.txt
* cat vs_code_extensions_list.txt | xargs -n 1 code --install-extension
# Delete extensions
* code --list-extensions | xargs -n 1 code --uninstall-extension
