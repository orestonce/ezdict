package ezdict

import (
	"encoding/xml"
	"testing"
)

func TestQueryWords(t *testing.T) {
	//resp, err := http.DefaultClient.Get("https://fanyi.youdao.com/fsearch?q=dict")
	//if err != nil {
	//	panic(err)
	//}
	//data, err := ioutil.ReadAll(resp.Body)
	//if err != nil {
	//	panic(err)
	//}
	//resp.Body.Close()
	//fmt.Println(string(data))

	var tmp TranslationInfo
	err := xml.Unmarshal([]byte(str), &tmp)
	if err != nil {
		panic(err)
	}
	if tmp.DictcnSpeach != "dict" {
		t.Fatal(tmp.DictcnSpeach)
		return
	}
	if tmp.TransType != "ec" {
		t.Fatal(tmp.TransType)
		return
	}
	if tmp.Content != "abbr. 词典，字典（dictionary）" {
		t.Fatal(tmp.Content)
		return
	}
}

const str = `<?xml version="1.0" encoding="UTF-8"?>
<yodaodict>
  <return-phrase><![CDATA[dict]]></return-phrase>
  
                            <phonetic-symbol></phonetic-symbol>
                  <dictcn-speach>dict</dictcn-speach>
                          <custom-translation>
        <type>ec</type>
                  <translation><content><![CDATA[abbr. 词典，字典（dictionary）]]></content></translation>
                </custom-translation>
          
              <yodao-web-dict>
                    <web-translation>
                <key><![CDATA[dict]]></key>
                          <trans><value><![CDATA[字典]]></value></trans>
                  <trans><value><![CDATA[词典]]></value></trans>
                  <trans><value><![CDATA[海词网]]></value></trans>
                  <trans><value><![CDATA[信息通讯技术文凭]]></value></trans>
                </web-translation>
              <web-translation>
                <key><![CDATA[INSTANT-DICT]]></key>
                          <trans><value><![CDATA[快译通]]></value></trans>
                  <trans><value><![CDATA[快译通电子辞典]]></value></trans>
                  <trans><value><![CDATA[牛津]]></value></trans>
                </web-translation>
              <web-translation>
                <key><![CDATA[SAME-DICT]]></key>
                          <trans><value><![CDATA[桑姆通译]]></value></trans>
                  <trans><value><![CDATA[桑姆]]></value></trans>
                  <trans><value><![CDATA[阃氲疟]]></value></trans>
                </web-translation>
            </yodao-web-dict>
    
                    	       		 <recommend><![CDATA[Dict]]></recommend>
     	       		 <recommend><![CDATA[DICT]]></recommend>
     	           <sexp>0</sexp>
</yodaodict>`
