# Contact Management System (BST) — How It Works

## Overview

This is a working Contact Management System built with a **Binary Search Tree (BST)**. The page lets you add, search, delete, and display contacts directly in your browser — no terminal, no installation needed.

## What the Page Does

| Feature | What It Does |
|---------|--------------|
| **Add Contact** | Type an ID, Name, and Phone, then click **Add Contact**. The contact is inserted into the BST by its unique ID. |
| **Search** | Type a Contact ID and click **Search**. The system finds the contact in the tree or shows "not found". |
| **Delete** | Type a Contact ID and click **Delete**. The contact is removed from the tree (all three deletion cases are handled). |
| **Display All** | Click **Display All** to see every contact sorted in ascending order of ID (inorder traversal). |
| **BST Visualization** | A live tree diagram shows the root and child nodes. When you search, the found node is highlighted in red. |
| **Contact Table** | A table lists all contacts with a Delete button for each row. |

## How the BST Works

- Each contact is stored in a **node** with: ID, Name, Phone, left child pointer, right child pointer.
- **BST Rule:** For every node, all IDs in the left subtree are smaller, and all IDs in the right subtree are larger.
- **Insert:** Start at root. Go left if new ID is smaller, right if larger, until you find an empty spot. Duplicate IDs are rejected.
- **Search:** Start at root. If target ID matches, found. If smaller, go left. If larger, go right. If you reach null, not found.
- **Delete:** Three cases:
  1. Leaf node → simply remove it.
  2. One child → replace the node with its child.
  3. Two children → replace with the inorder successor (smallest ID in right subtree), then delete that successor.
- **Display (Inorder):** Visit left subtree, then root, then right subtree. This prints contacts in ascending ID order automatically.

## Files

| File | Purpose |
|------|---------|
| `index.html` | The interactive web page (just the functions — no descriptions) |
| `contact_management_system.c` | The full C source code for local compilation |
| `description.md` | This file — how the system works |

## How to Use the Web Page

1. Open `index.html` in any browser (Chrome, Edge, Safari, Firefox).
2. Type an ID, Name, and Phone in the input boxes.
3. Click **Add Contact** to add it.
4. Click **Search** to find a contact by ID.
5. Click **Delete** to remove a contact.
6. Click **Display All** to see all contacts sorted by ID.
7. The BST diagram and table update automatically after every action.

## How to Run the C Code Locally

```bash
gcc contact_management_system.c -o cms
./cms
```
(On Windows: `cms.exe`)

Follow the menu: 1=Add, 2=Search, 3=Delete, 4=Display, 5=Exit.
