set nocompatible
set tags=~/AOS/src/tags
set hls
set nu
set ai
colors desert 
syntax on
set sw=4
set ts=4
set whichwrap+=[,]
set backspace=indent,eol,start 
set showcmd
set ruler
filetype plugin indent on
set showmatch
set wildmenu
set incsearch
set statusline=%f%m%r%h%w[%L][%{&ff}]%y[%p%%][%04l,%04v]
set cursorline
set laststatus=2
set si
set path+=~/AOS/src/**
set nospell
"set nonumber
set wrap
"set paste
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1

" Only do this part when compiled with support for autocommands
if has("autocmd")
" " In text files, always limit the width of text to 78 characters
autocmd BufRead *.txt set tw=78
" " When editing a file, always jump to the last cursor position
autocmd BufReadPost *
\ if line("'\"") > 0 && line ("'\"") <= line("$") |
\ exe "normal g'\"" |
\ endif
endif


"-----------------------------------------------------------
" folding
"-----------------------------------------------------------
"enable folding, i find it very useful
"set nofen
"set fdl=0
"set lbr


"-----------------------------------------------------------
" for favarite c/c++
"-----------------------------------------------------------
" normal mode
autocmd filetype c map<silent><buffer> <f6> :w<cr>:make<cr>:cw<cr>
autocmd filetype cpp map<silent><buffer> <f6> :w<cr>:make<cr>:cw<cr>

"-----------------------------------------------------------
" For special script file type
" I only need to use python,lua,sh and surely only know these
"-----------------------------------------------------------
" normal mode
autocmd filetype python map<buffer> <f5> :!clear<cr>:w<cr>:!python %<cr>
autocmd filetype lua map<buffer> <f5> :!clear<cr>:w<cr>:!lua %<cr>
autocmd filetype sh map<buffer> <f5> :!clear<cr>:w<cr>:!./%<cr>
" insert mode
autocmd filetype python imap<buffer> <f5> <esc>:!clear<cr>:w<cr>:!python %<cr>
autocmd filetype lua imap<buffer> <f5> <esc>:!clear<cr>:w<cr>:!lua %<cr>
autocmd filetype sh imap<buffer> <f5> <esc>:!clear<cr>:w<cr>:!./%<cr>
"-----------------------------------------------------------

"-----------------------------------------------------------
" taglist
"-----------------------------------------------------------
let Tlist_Exit_OnlyWindow = 1
let Tlist_Use_Right_Window = 1
let Tlist_File_Fold_Auto_Close = 1
map <leader>to :Tlist<cr>

so $VIMRUNTIME/syntax/xml.vim
let b:current_syntax = "lzx"
" * Q_LZ_COPYRIGHT_BEGIN ******************************************************
" * Copyright 2001-2004 Laszlo Systems, Inc.  All Rights Reserved.            *
" * Use is subject to license terms.                                          *
" * A_LZ_COPYRIGHT_END ********************************************************

syn region lzxScript start=+<script>+ end=+</script>+ extend containedin=xmlRegion contains=lzxCData,xmlTag,xmlEqual,xmlEndTag fold keepend

syn region lzxMethod start=+<method+ end=+</method>+ extend containedin=xmlRegion contains=lzxCData,xmlTag,xmlEqual,xmlEndTag fold keepend

syn region lzxEventHandler start=+\Won\w\{-}="+ end=+"+ containedin=xmlTag contains=xmlAttrib,xmlEqual,lzxScriptAttribute,lzxAttributeQuote contained keepend

syn region  lzxScriptAttribute  matchgroup=lzxAttributeQuote start=+="+ end=+"+  contained 

hi link  lzxAttributeQuote           String 

"uncomment these lines to enable syntax folding
"set foldmethod=syntax  
"set foldlevel=2
"highlight Folded guibg=#FFF0F0 guifg=#666688

"tag matching
:source $VIMRUNTIME/macros/matchit.vim
if !exists("b:match_words") |
    \ let b:match_ignorecase=0 | let b:match_words =
    \ '<:>,' .
    \ '<\@<=!\[CDATA\[:]]>,'.
    \ '<\@<=!--:-->,'.
    \ '<\@<=?\k\+:?>,'.
    \ '<\@<=\([^ \t>/]\+\)\%(\s\+[^>]*\%([^/]>\|$\)\|>\|$\):<\@<=/\1>,'.
    \ '<\@<=\%([^ \t>/]\+\)\%(\s\+[^/>]*\|$\):/>'
    \ | endif

"highlights CDATA in a method as a comment
syn match    lzxCData   +<!\[CDATA\[+  contained 
syn match    lzxCData   +]]>+          contained 

hi link  lzxCData           String 

"js comments
syn match   javaScriptLineComment      "\/\/.*$" containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScriptCommentSkip      "^[ \t]*\*\($\|[ \t]\+\)"
syn region  javaScriptCommentString    start=+"+  skip=+\\\\\|\\"+  end=+"+ end=+\*/+me=s-1,he=s-1 contains=javaScriptSpecial,javaScriptCommentSkip,@htmlPreproc
syn region  javaScriptComment2String   start=+"+  skip=+\\\\\|\\"+  end=+$\|"+  contains=javaScriptSpecial,@htmlPreproc
syn region  javaScriptComment          start="/\*"  end="\*/" contains=javaScriptCommentString,javaScriptCharacter,javaScriptNumber containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScriptSpecial          "\\\d\d\d\|\\." containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn region  javaScriptStringD          start=+"+  skip=+\\\\\|\\"+  end=+"+  contains=javaScriptSpecial,@htmlPreproc containedin=lzxMethod
syn region  javaScriptStringS          start=+'+  skip=+\\\\\|\\'+  end=+'+  contains=javaScriptSpecial,@htmlPreproc containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScriptSpecialCharacter "'\\.'" containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScriptNumber           "-\=\<\d\+L\=\>\|0[xX][0-9a-fA-F]\+\>" containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptConditional      if else containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptRepeat           while for containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptBranch           break continue switch case default containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptOperator         new in containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptType             super this var parent containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptStatement        return with containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptFunction         function containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn keyword javaScriptBoolean          true false containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScriptBraces           "[{}]" containedin=lzxMethod,lzxScriptAttribute,lzxScript

" catch errors caused by wrong parenthesis
syn match   javaScriptInParen     contained "([{}])"
syn region  javaScriptParen       transparent start="(" end=")" contains=javaScriptParen,javaScript.* containedin=lzxMethod,lzxScriptAttribute,lzxScript
syn match   javaScrParenError  ")" containedin=lzxMethod,lzxScriptAttribute

hi def link javaScriptComment           Comment
hi def link javaScriptLineComment       Comment
hi def link javaScriptSpecial           Special
hi def link javaScriptStringS           String
hi def link javaScriptStringD           String
hi def link javaScriptCharacter         Character
hi def link javaScriptSpecialCharacter  javaScriptSpecial
hi def link javaScriptNumber            javaScriptValue
hi def link javaScriptConditional       Conditional
hi def link javaScriptRepeat            Repeat
hi def link javaScriptBranch            Conditional
hi def link javaScriptOperator          Operator
hi def link javaScriptType              Type
hi def link javaScriptStatement         Statement
hi def link javaScriptFunction          Function
hi def link javaScriptBraces            Function
hi def link javaScriptError             Error
hi def link javaScrParenError           javaScriptError
hi def link javaScriptInParen           javaScriptError
hi def link javaScriptBoolean           Boolean

function! CommNode()
    if &foldopen =~ "percent"
      normal! zv
    endif

    let cline = line(".")
    while match( getline(cline) , "<\!\\@!" ) < 0
        let cline = cline -1
        if cline == -1
            break
        endif
    endwhile
    if cline >=0
        let oldline = getline(cline)
        let commtag = matchstr( oldline , "<\\w*" )
        "let nline = substitute( oldline  , "<" , "<!--" , "" )
        "let didrep = setline( cline , nline )
    else
        echo "Couldn't find node to comment."
        return
    endif 
    echo "commtag: " . commtag
endfun


map <C-F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>

"for tagging
let Tlist_Auto_Open=1
set tags=tags;
set autochdir 

"""""""""""""""""""""""cscope config""""""""""""""""""      
"set cscopequickfix=s-,c-,d-,i-,t-,e-    
set cscopequickfix=   
if has("cscope")    
set csprg=/usr/bin/cscope    
set csto=1    
set cst    
set nocsverb    
" add any database in current directory     
if filereadable("cscope.out")    
   cs add cscope.out    
endif    
set csverb    
endif    
  
nmap <C-@>s :cs find s <C-R>=expand("<cword>")<CR><CR>  
nmap <C-@>g :cs find g <C-R>=expand("<cword>")<CR><CR>  
nmap <C-@>c :cs find c <C-R>=expand("<cword>")<CR><CR>  
nmap <C-@>t :cs find t <C-R>=expand("<cword>")<CR><CR>  
nmap <C-@>e :cs find e <C-R>=expand("<cword>")<CR><CR>  
nmap <C-@>f :cs find f <C-R>=expand("<cfile>")<CR><CR>  
nmap <C-@>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>  
nmap <C-@>d :cs find d <C-R>=expand("<cword>")<CR><CR> 

""""""""""""""""""""""ctags config"""""""""""""""""""
set tags=tags;
set tags+=~/.vim/systags
