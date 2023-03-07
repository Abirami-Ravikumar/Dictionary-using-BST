    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    struct dictionary
    {
    	char word[150], meaning[300];
        struct dictionary *left, *right;
    }*root = NULL;
    typedef struct dictionary dict;



    dict * createNode(char *word, char *meaning)
    {
            dict *newnode;
            newnode=(dict *)malloc(sizeof(dict));
            strcpy(newnode->word, word);
            strcpy(newnode->meaning, meaning);
            newnode->left = newnode->right = NULL;
            return newnode;
    }



    int insert(char *word, char *meaning)
    {
    	dict *par=NULL,*newnode=NULL;
        int res = 0;
        if (!root)
    	{
    		root=createNode(word, meaning);
    	}
    	else
    	{
    	    dict *cur=root;
            while(cur!=NULL)
    	    {
    		    res=strcasecmp(word,cur->word);
                if(res==0)
    			 {   printf("Word already exists!!!\n");return 0;break;
    			 }
                par=cur;
                if(res>0)
                    cur=cur->right;
                else
                    cur=cur->left;
    	    }
            newnode=createNode(word, meaning);
            //fwrite(word,meaning,fp);  -------- to write into csv file
            if(res>0)
                par->right=newnode;
            else
                par->left=newnode;
    	}
    	return 1;
    }



    dict* find_minimum(dict *root)
    {
        if(root == NULL)
            return NULL;
        else if(root->left != NULL)
            return find_minimum(root->left);
        return root;
    }
    dict* delete(dict *root, char* word)
    {
        if(root==NULL)
        {    printf("The word \"%s\" is not found in the Dictionary\n",word);return NULL; }
        if (strcasecmp(word,root->word)>0)
            root->right = delete(root->right, word);
        else if(strcasecmp(word,root->word)<0)
            root->left= delete(root->left, word);






        else
        {
            if(root->left==NULL && root->right==NULL)
            {
                printf("You've deleted the word \"%s\" from the Dictionary\n",root->word);
                free(root);
                return NULL;
            }
            else if(root->left==NULL || root->right==NULL)
            {
                dict *temp;
                if(root->left==NULL)
                {
                    temp = root->right;
                    printf("You've deleted the word \"%s\" from the Dictionary\n",root->word);
                }
                else
                {
                    temp = root->left;
                    printf("You've deleted the word \"%s\" from the Dictionary\n",root->word);
                }
                free(root);
                return temp;
            }



            else
            {
                dict *temp = find_minimum(root->right);
                root = temp;
                root->right = delete(root->right, temp->word);
            }
        }
        return root;
    }



    void search(char *word)
    {
    	dict *temp=NULL;
        int flag=0;
        temp=root;
    	while(temp)
    	{
    		if (strcasecmp(word,temp->word)==0)
    		{
    			printf("Word   : %s\n", word);
                printf("Meaning: %s\n", temp->meaning);
                flag = 1;
                break;
            }



            if(strcasecmp(word,temp->word)<0)
                temp=temp->left;
            else
                temp=temp->right;
            }
            if(flag==0)
                printf("The word \"%s\" is not found in the Dictionary\n",word);
    }


    void editmeaning(char *word, char *meaning)
    {
    	dict *temp=NULL;
        int flag=0;
        temp=root;
    	while(temp)
    	{
    		if (strcasecmp(word,temp->word)==0)
    		{
    			strcpy(temp->meaning, meaning);
    			printf("You've edited the meaning of the word \"%s\"\n",temp->word);
    			printf("The new meaning is \n");
    			//fwrite(word,temp->meaning,fp);  -------- to write into csv file
    			printf("Word   : %s\n", word);
                printf("Meaning: %s\n", temp->meaning);
    			flag = 1;
                break;
            }
            if(strcasecmp(word,temp->word)<0)
                temp=temp->left;
            else
                temp=temp->right;
            }
            if(flag==0)
                    printf("The word \"%s\" is not found in the Dictionary\n",word);
    }


    void inorder(dict *myNode)
    {
        int i=1;
        dict *temp=myNode;
    	void view(dict *temp)
    	{
    		if (temp)
    		{
    			view(temp->left);
    			printf("%-5d   %-20s      :     %-30s\n",i, temp->word, temp->meaning);i++;
    			view(temp->right);
    		}
        }
        view(temp);
    }




    int main()
    {
        int ch;
        char word[150], meaning[300];
        FILE *fp = fopen("dict.csv","r");
        if(fp==NULL)
        {
            printf("Something went wrong...\n");
        }
        char line[1000];
        char *w;
        char *m;
		while(fgets(line, 1000, fp) != NULL)
		{
			printf("\n%s",line);
			w = strtok(line, ",");
			m = strtok(NULL,",");
			insert(w,m);
        }
        fclose(fp);


        while (1)
    	{
    		printf("\nDICTIONARY\n");
    		printf("1. Insertion   \t2. Deletion\n");
            printf("3. Searching   \t4. View Dictionary\n");
    		printf("5. Edit meaning\t6. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);
            getchar();
            switch (ch)
    		{
    			case 1:
    					printf("Enter the Word to insert with meaning:\n");
                        fgets(word, 100, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(word[x]=='\n')
    						{
    							word[x]='\0';break;
    						}
    					}
                        fgets(meaning, 256, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(meaning[x]=='\n')
    						{
    							meaning[x]='\0';break;
    						}
    					}
                        if(insert(word, meaning)==1)
                            printf("You've inserted the word \"%s\" into the Dictionary\n",word);
                        break;
                case 2:
                        printf("Enter the word to delete:\n");
                        fgets(word, 100, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(word[x]=='\n')
    						{
    							word[x]='\0';break;
    						}
    				    }
    					delete(root,word);
                        break;
                case 3:
                        printf("Enter the search word:\n");
                        fgets(word, 100, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(word[x]=='\n')
    						{
    							word[x]='\0';break;
    						}
    					}
                        search(word);
                        break;
                case 4:
    					printf("        Word                      :     Meaning\n");
    					inorder(root);

    						break;
    		    case 5:
    					printf("Enter word and it's new meaning:\n");
                        fgets(word, 100, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(word[x]=='\n')
    						{
    							word[x]='\0';break;
    						}
    					}
                        fgets(meaning, 256, stdin);
    					for(int x=0;x<=100;x++)
    					{
    						if(meaning[x]=='\n')
    						{
    							meaning[x]='\0';break;
    						}
    					}
                        editmeaning(word, meaning);
                        break;
                case 6:
                        exit(0);
                default:
                        printf("Invalid option... Choose between 1-6\n");
                        break;
                }
            }
            return 0;
      }

