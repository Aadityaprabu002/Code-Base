package main

import (
	"fmt"
	"html/template"
	"net/http"
	"os"
	"os/exec"
	"strings"
)

type output struct {
	Msg string
}

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

		curDir, _ := os.Getwd()
		os.Chdir("../codes")

		filename := fmt.Sprintf("../codes/%s.%s", "sample", strings.ToLower(lang))

		_ = os.WriteFile(filename, []byte(code), 0777)

		result, _ := exec.Command("powershell.exe", "../compiler/run.exe", lang, "sample").Output()

		os.Remove(filename)
		fmt.Println("Output:", string(result))

		t, _ := template.ParseFiles("../templates/editor.html")
		Msg := string(result)
		op := output{Msg}

		t.Execute(w, op)
		os.Chdir(curDir)

	}

}
func home(w http.ResponseWriter, r *http.Request) {
	t, _ := template.ParseFiles("../templates/home.html")
	t.Execute(w, nil)
}
