package routes

import (
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"os/exec"
	"strings"
	"text/template"
)

func Editor(w http.ResponseWriter, r *http.Request) {

	// Logging Incoming Requests
	logRequestDetails(*r)

	// Get request
	if r.Method == "GET" {
		serveEditorHtmlParsed(w, "", "")
		return
	}

	// Post Request (Editor Form Submission)
	if r.Method == "POST" {

		// Parsing Form Data
		err := r.ParseForm()
		handlerErr(err)

		code := r.Form["code"][0]
		lang := r.Form["language"][0]

		// Checking Form The Incomming Code
		if code == "" {
			serveEditorHtmlParsed(w, "", "")
			return
		}

		if !inListOfLanguageSupported(lang) {
			serveEditorHtmlParsed(w, "", "")
			return
		}

		tmpfile, err := ioutil.TempFile(".", "code-"+lang+"-"+"*"+"."+lang)
		handlerErr(err)

		defer os.Remove(tmpfile.Name()) // clean up

		n, err := tmpfile.Write([]byte(code))
		log.Println("Wrote ", n, "Bytes Into ", tmpfile.Name())
		handlerErr(err)

		// log.Println(exec.Command("chmod", "777", tmpfile.Name()).String())

		// err = exec.Command("chmod", "777", tmpfile.Name()).Run()
		// handlerErr(err)

		// err = exec.Command("chown", "code-base", tmpfile.Name()).Run()
		// handlerErr(err)

		// ls, err := exec.Command("ls", "-al").Output()
		// handlerErr(err)
		// log.Println(string(ls))

		err = tmpfile.Close()
		handlerErr(err)

		log.Println("File Name: ", tmpfile.Name())

		serveEditorHtmlParsed(w, code, shellExecuter(lang, tmpfile.Name(), "input.txt", "5"))

	}

}

func shellExecuter(lang, file, input_file, timeout string) string {

	cmd := exec.Command("./executor.exe", lang, file, input_file, timeout)

	log.Println("Executed Command: ", cmd.String())

	output, err := cmd.CombinedOutput()

	if err != nil {
		log.Println("Error in getting output of command Err ", err)
		return ""
	}

	return string(output)

}

func serveEditorHtmlParsed(w http.ResponseWriter, code, output string) {
	editorHTML = originalEditorHTML
	template, err := template.New("EditorTemplate").Parse(string(editorHTML))

	handlerErr(err)

	if output == "" {
		template.Execute(w, struct {
			Code   string
			Result string
			Time   string
		}{
			code,
			"",
			"",
		})
		return
	}

	code_output := strings.Split(output, "Time: ")

	template.Execute(w, struct {
		Code   string
		Result string
		Time   string
	}{
		code,
		code_output[0],
		"Time: " + code_output[1],
	})
}
