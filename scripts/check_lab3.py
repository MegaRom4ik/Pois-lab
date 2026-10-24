"""Check actual class declarations and domain line coverage for lab 3."""
import json
import re
import sys
from pathlib import Path


def check_model(folder):
    classes = []
    fields = 0
    behaviors = 0
    for header in sorted((folder / "include").glob("*.hpp")):
        declaration = header.read_text()
        match = re.search(r"class (\w+) \{", declaration)
        if not match:
            continue
        name = match.group(1)
        classes.append((name, declaration))
        private = declaration.split("private:", 1)[1].split("};", 1)[0]
        fields += len(re.findall(r"\w+_;", private))
        source = (folder / "src" / (name + ".cpp")).read_text()
        behaviors += len(re.findall(r"\b" + name + r"::(?!" + name + r"\b)\w+\s*\(", source))
    associations = 0
    for name, declaration in classes:
        private = declaration.split("private:", 1)[1].split("};", 1)[0]
        parameters = " ".join(re.findall(r"\(([^)]*)\)", declaration))
        declaration = private + " " + parameters
        for other, _ in classes:
            if other != name and re.search(r"\b" + other + r"\b", declaration):
                associations += 1
    errors = len(list((folder / "include").glob("*Error.hpp")))
    values = {"classes": len(classes), "fields": fields, "behaviors": behaviors,
              "associations": associations, "exceptions": errors}
    minimum = {"classes": 50, "fields": 150, "behaviors": 100,
               "associations": 30, "exceptions": 12}
    print(values)
    for key, count in values.items():
        if count < minimum[key]:
            sys.exit(f"Not enough {key}: {count}")


def check_coverage(path):
    report = json.loads(path.read_text())
    entries = {Path(item["filename"]).name: item for item in report["data"][0]["files"]}
    expected = {p.name for p in Path("lab3/src").glob("*.cpp")}
    if not expected or not expected.issubset(entries):
        sys.exit("Missing lab3 domain coverage")
    total, covered = 0, 0
    insufficient = []
    for name in sorted(expected):
        lines = entries[name]["summary"]["lines"]
        count = lines["count"]
        percentage = 100 * lines["covered"] / count if count else 0
        print(f"{name}: {percentage:.2f}% lines")
        if percentage <= 90:
            insufficient.append(name)
        total += count
        covered += lines["covered"]
    percentage = 100 * covered / total if total else 0
    print(f"Lab 3 domain: {percentage:.2f}% lines")
    if percentage <= 90 or insufficient:
        sys.exit("Coverage must exceed 90% for every class: " + ", ".join(insufficient))


if sys.argv[1] == "model":
    check_model(Path(sys.argv[2]))
elif sys.argv[1] == "coverage":
    check_coverage(Path(sys.argv[2]))
else:
    sys.exit("Expected model or coverage")
