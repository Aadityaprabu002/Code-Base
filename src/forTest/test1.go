package main

import (
	"fmt"
	"os"
)

func main() {
	// a, _ := exec.Command("powershell.exe", "./test1").Output()
	// fmt.Println(string(a))

	fmt.Println(os.Getwd())
	os.Chdir("../codes")
	fmt.Println(os.Getwd())

}
