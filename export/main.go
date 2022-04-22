package main

import (
	"github.com/orestonce/ezdict"
	"github.com/orestonce/go2cpp"
)

func main() {
	ctx := go2cpp.NewGo2cppContext(go2cpp.NewGo2cppContext_Req{
		CppBaseName:                 "golib",
		EnableQtClass_RunOnUiThread: true,
	})
	ctx.Generate1(ezdict.EventCancel)
	ctx.Generate1(ezdict.QueryWords)
	ctx.MustCreateAmd64LibraryInDir("ezdict-qt")
}
