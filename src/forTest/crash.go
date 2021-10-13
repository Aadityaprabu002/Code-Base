package main

import (
	"html/template"
	"os"
)

type page struct {
	Name string
}

func main() {
	person := page{"aaditya"}
	t, _ := template.ParseFiles("../templates/sample.html")
	t.Execute(os.Stdout, person)
}
