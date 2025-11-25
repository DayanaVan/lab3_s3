package main

import (
	"fmt"
	. "l1/array"
	. "l1/forwardlist"
	. "l1/hashtable"
	. "l1/list"
	. "l1/queue"
	. "l1/stack"
	"os"
	"strconv"
)

func printHelp() {
	fmt.Println("Usage: ./l1 [FILE] [COMMAND] [ARGUMENTS]")
}

func main() {
	argc := len(os.Args)
	argv := os.Args

	if argc < 3 {
		printHelp()
		return
	}

	file := argv[1]
	switch argv[2][0] {
	case 'A':
		arr, err := ReadArrayFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "ADD":
			if argc != 4 {
				printHelp()
				return
			}
			arr.Add(argv[3])

			arr.WriteToFile(file)
		case "INSERT":
			if argc != 5 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			arr.Insert(argv[3], index)

			arr.WriteToFile(file)
		case "GET":
			if argc != 4 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			fmt.Println(arr.Get(index))
		case "REMOVE":
			if argc != 4 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			arr.Remove(index)

			arr.WriteToFile(file)
		case "CHANGE":
			if argc != 5 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			arr.Change(index, argv[4])

			arr.WriteToFile(file)
		case "SIZE":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Println(arr.GetSize())
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Println(arr.ToString())
		default:
			fmt.Println("Неизвестная операция")
		}
	case 'F':
		fl, err := ReadForwardListFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "ADDTAIL":
			if argc != 4 {
				printHelp()
				return
			}
			fl.AddTail(argv[3])

			fl.WriteToFile(file)
		case "ADDHEAD":
			if argc != 4 {
				printHelp()
				return
			}
			fl.AddHead(argv[3])

			fl.WriteToFile(file)
		case "INSERT":
			if argc != 5 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			fl.Insert(argv[3], index)

			fl.WriteToFile(file)
		case "REMOVETAIL":
			if argc != 3 {
				printHelp()
				return
			}
			fl.RemoveTail()

			fl.WriteToFile(file)
		case "REMOVEHEAD":
			if argc != 3 {
				printHelp()
				return
			}
			fl.RemoveHead()

			fl.WriteToFile(file)
		case "REMOVEINDEX":
			if argc != 4 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			fl.Remove(index)

			fl.WriteToFile(file)
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Printf("С головы: %s\nС хвоста %s\n", fl.PrintFromHead(), fl.PrintFromTail())
		case "REMOVE":
			if argc != 5 {
				printHelp()
				return
			}
			num, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Номер вхождения не число")
				return
			}
			fl.RemoveKey(argv[3], num)

			fl.WriteToFile(file)
		case "FIND":
			if argc != 5 {
				printHelp()
				return
			}
			num, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Номер вхождения не число")
				return
			}
			if fl.Find(argv[3], num) != nil {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}
		}
	case 'L':
		fl, err := ReadListFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "ADDTAIL":
			if argc != 4 {
				printHelp()
				return
			}
			fl.AddTail(argv[3])

			fl.WriteToFile(file)
		case "ADDHEAD":
			if argc != 4 {
				printHelp()
				return
			}
			fl.AddHead(argv[3])

			fl.WriteToFile(file)
		case "INSERT":
			if argc != 5 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			fl.Insert(argv[3], index)

			fl.WriteToFile(file)
		case "REMOVETAIL":
			if argc != 3 {
				printHelp()
				return
			}
			fl.RemoveTail()

			fl.WriteToFile(file)
		case "REMOVEHEAD":
			if argc != 3 {
				printHelp()
				return
			}
			fl.RemoveHead()

			fl.WriteToFile(file)
		case "REMOVEINDEX":
			if argc != 4 {
				printHelp()
				return
			}
			index, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Индекс не число")
				return
			}
			fl.Remove(index)

			fl.WriteToFile(file)
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Printf("С головы: %s\nС хвоста %s\n", fl.PrintFromHead(), fl.PrintFromTail())
		case "REMOVE":
			if argc != 5 {
				printHelp()
				return
			}
			num, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Номер вхождения не число")
				return
			}
			fl.RemoveKey(argv[3], num)

			fl.WriteToFile(file)
		case "FIND":
			if argc != 5 {
				printHelp()
				return
			}
			num, err := strconv.Atoi(argv[4])
			if err != nil {
				fmt.Println("Номер вхождения не число")
				return
			}
			if fl.Find(argv[3], num) != nil {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}
		}
	case 'Q':
		q, err := ReadQueueFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "PUSH":
			if argc != 4 {
				printHelp()
				return
			}
			q.Push(argv[3])

			q.WriteToFile(file)
		case "POP":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Println(q.Pop())

			q.WriteToFile(file)
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Printf("С начала %s\n", q.Print())
		}
	case 'S':
		s, err := ReadStackFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "PUSH":
			if argc != 4 {
				printHelp()
				return
			}
			s.Push(argv[3])

			s.WriteToFile(file)
		case "POP":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Println(s.Pop())

			s.WriteToFile(file)
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Printf("С конца %s\n", s.Print())
		}
	case 'H':
		ht, err := ReadHashTableFromFile(file)
		if err != nil {
			fmt.Println("file bad")
			break
		}
		switch argv[2][1:] {
		case "ADD":
			if argc != 5 {
				printHelp()
				return
			}
			key, err1 := strconv.Atoi(argv[3])
			value, err2 := strconv.Atoi(argv[4])
			if err1 != nil || err2 != nil {
				fmt.Println("Ключ или значение - не число")
				break
			}
			ht.Insert(key, value)

			ht.WriteToFile(file)
		case "REMOVE":
			if argc != 4 {
				printHelp()
				return
			}
			key, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Ключ не число")
				return
			}
			ht.Remove(key)

			ht.WriteToFile(file)
		case "FIND":
			if argc != 4 {
				printHelp()
				return
			}
			key, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Ключ не число")
				return
			}
			if ht.Contains(key) {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}
		case "GET":
			if argc != 4 {
				printHelp()
				return
			}
			key, err := strconv.Atoi(argv[3])
			if err != nil {
				fmt.Println("Ключ не число")
				return
			}
			val, err := ht.Get(key)
			if err != nil {
				fmt.Println("Не найдено")
			} else {
				fmt.Println(val)
			}
		case "PRINT":
			if argc != 3 {
				printHelp()
				return
			}
			fmt.Println(ht.ToString())
		default:
			fmt.Println("Неизвестная операция")
		}
	default:
		fmt.Println("Неизвестная структура")
	}
}
