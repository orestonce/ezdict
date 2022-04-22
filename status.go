package ezdict

import (
	"encoding/xml"
	"io/ioutil"
	"net/http"
	"net/url"
)

type QueryWords_Resp struct {
	Skipped bool
	ErrMsg  string
	Info    TranslationInfo
}

type TranslationInfo struct {
	XMLName      xml.Name
	DictcnSpeach string `xml:"dictcn-speach"`
	TransType    string `xml:"custom-translation>type"`
	Content      string `xml:"custom-translation>translation>content"`
}

func QueryWords(words string) (resp QueryWords_Resp) {
	if words == "" {
		resp.Skipped = true
		return resp
	}

	ctx, cancelFn := NewContext()
	defer cancelFn()

	// 开始查询信息
	getReq, err := http.NewRequest("GET", "https://fanyi.youdao.com/fsearch?q="+url.QueryEscape(words), nil)
	if err != nil {
		resp.ErrMsg = "err0 " + err.Error()
		resp.Skipped = IsContextCancel(ctx)
		return resp
	}
	getReq = getReq.WithContext(ctx)
	resp0, err := http.DefaultClient.Do(getReq)
	if err != nil {
		resp.ErrMsg = "err1 " + err.Error()
		resp.Skipped = IsContextCancel(ctx)
		return resp
	}
	data, err := ioutil.ReadAll(resp0.Body)
	_ = resp0.Body.Close()
	if err != nil {
		resp.ErrMsg = "err2 " + err.Error()
		resp.Skipped = IsContextCancel(ctx)
		return resp
	}
	err = xml.Unmarshal(data, &resp.Info)
	if err != nil {
		resp.ErrMsg = "err3 " + err.Error()
		return resp
	}
	return resp
}
