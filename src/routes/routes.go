// Copyright 2020 Team Code-Base. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

package routes

import (
	_ "embed"
	"log"
	"net/http"
)

//go:embed static/editor.html
var editorHTML []byte

//go:embed static/editor.html
var originalEditorHTML []byte

var listOfLanguageSupported []string = []string{
	"C",
	"CPP",
	"JAVA",
	"PY",
}

func logRequestDetails(req http.Request) {
	log.Println("Request", req.Method, req.URL, "From", req.RemoteAddr)
}

func handlerErr(err error) {
	if err != nil {
		log.Println(err)
	}
}

func inListOfLanguageSupported(receivedLang string) bool {
	for _, lang := range listOfLanguageSupported {
		if lang == receivedLang {
			return true
		}
	}
	return false
}
