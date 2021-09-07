package main

import (
	"fmt"
	"html/template"
	"net/http"
	"os"
	"os/exec"
	"strings"
)

func main() {
	http.HandleFunc("/", home)
	http.HandleFunc("/editor", editor)
	http.ListenAndServe(":4040", nil)
}
func editor(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		t, _ := template.ParseFiles("../templates/editor.html")
		t.Execute(w, nil)
	} else {
		r.ParseForm()
		code := r.Form["code"][0]
		lang := r.Form["language"][0]
		fmt.Println(code)
		os.WriteFile(fmt.Sprintf("C:/Users/USER/Desktop/go-workspace/src/codes/sample.%s", strings.ToLower(lang)), []byte(code), 0666)
		cmd := exec.Command("powershell.exe", "C:/Users/USER/Desktop/go-workspace/src/codes/run.exe", lang, "sample")
		fmt.Println(cmd.Run())
		t, _ := template.ParseFiles("../templates/editor.html")
		t.Execute(w, nil)
	}
}
func home(w http.ResponseWriter, r *http.Request) {
	t, _ := template.ParseFiles("../templates/home.html")
	t.Execute(w, nil)
}
