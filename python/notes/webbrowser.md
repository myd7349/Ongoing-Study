[How can I open a website in my web browser using Python?](https://stackoverflow.com/questions/31715119/how-can-i-open-a-website-in-my-web-browser-using-python)

```python
import webbrowser
webbrowser.open('http://google.co.kr', new=2)
webbrowser.open_new('http://google.co.kr')
webbrowser.open_new_tab('http://google.co.kr')
```

