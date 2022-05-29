List<string> dinosaurs = new List<string>();
dinosaurs.Add("Tyrannosaurus");
dinosaurs.Add("Amargasaurus");
dinosaurs.Add("Deinonychus");
dinosaurs.Add("Compsognathus");

ReadOnlyCollection<string> readOnlyDinosaurs = new ReadOnlyCollection<string>(dinosaurs);
readOnlyDinosaurs.Dump();

dinosaurs.Add("Apple");
readOnlyDinosaurs.Dump();

// References:
// [What is a read only collection?](https://stackoverflow.com/questions/2680816/what-is-a-read-only-collection)
