# 技巧 / 黑科技

根据 [wikipedia (截至2025.6.6)](https://zh.wikipedia.org/wiki/Help:%E5%A6%82%E4%BD%95%E8%AE%BF%E9%97%AE%E7%BB%B4%E5%9F%BA%E7%99%BE%E7%A7%91), 使用以下参数打开浏览器可以在墙内访问维基百科（进行编辑）:

```sh
--host-rules="MAP *.wikipedia.org wikidata.org, MAP commons.wikimedia.org wikidata.org" --host-resolver-rules="MAP upload.wikimedia.org 208.80.154.240, MAP wikidata.org 185.15.59.224"
```

示例： `chromium`

```sh
chromium --host-rules="MAP *.wikipedia.org wikidata.org, MAP commons.wikimedia.org wikidata.org" --host-resolver-rules="MAP upload.wikimedia.org 208.80.154.240, MAP wikidata.org 185.15.59.224"
```

打开浏览器提示不受支持，安全性下降是正常的，忽略即可。

原理：修改 SNI（我也不知道是啥）
