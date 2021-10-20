// Copyright 2020 Team Code-Base. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

package main

import (
	"Code-Base/routes"
	"log"
	"net/http"
	"os"
	"os/exec"
	"runtime"
)

func init() {
	// Building Executer Everytime When Go Program Is Started
	cmd := exec.Command("sh", "./script.sh")

	if runtime.GOOS == "windows" {
		cmd.Path = "powershell.exe"
	}

	cmd.Dir = "."

	err := cmd.Run()
	if err != nil {
		log.Println(cmd.Stdout)
		log.Println(cmd.Stderr)
		log.Println("Err: ", err)
		log.Println("Error in building executor!")
		os.Exit(1)
		return
	} else {
		log.Println("Executer Built Succesfully")
	}

}

func main() {

	// Port 4040 Is Used
	var port string = "4040"

	// Temporary
	http.HandleFunc("/", routes.Editor)

	// Editor Handler
	http.HandleFunc("/editor", routes.Editor)

	// Listening Port 4040
	log.Println("Started Listening To Port : ", port)
	log.Println("Visit http://localhost:4040/ ...")
	http.ListenAndServe(":"+port, nil)
}
