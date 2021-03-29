#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <string.h> 

void usage(void) 
{ 
        printf("altairadjust infile outfile\n"); 
} 

int main(int argc, char *argv[]) 
{ 
        int fdread, fdwrite; 
        int tracks, sectors_per_track, sector_size, track_size; 
        int c; 
        char infile[254], outfile[254]; 
        char *data, *cp; 
        int bytes; 
        int ret; 

        if (argc != 3){ 
                usage(); 
                exit(1); 
        } 
        strcpy(infile,argv[1]); 
        strcpy(outfile,argv[2]); 
        tracks = 254; 
        sectors_per_track = 32; 
        sector_size = 137; 
        if ((fdwrite = open(outfile, O_RDONLY)) != -1){ 
                printf("%s already exists!  Continue? (y/n) ", outfile); 
                c = getchar(); 
                if (c != 'Y' && c != 'y'){ 
                        close(fdwrite); 
                        printf("Stopping\n"); 
                        exit(1); 
                } 
        } 
        close(fdwrite); 
        if ((fdwrite = open(outfile, O_CREAT | O_TRUNC | O_WRONLY ))
== -1){ 
                printf("Unable to open %s for writing\n", outfile); 
                exit(1); 
        } 
        if ((fdread = open(infile, O_RDONLY)) == -1){ 
                close(fdwrite); 
                printf("Unable to open %s for reading\n", infile); 
                exit(1); 
        } 
        track_size = sectors_per_track * sector_size; 
        bytes = tracks * track_size; 
        if ((data = malloc(bytes)) == NULL){ 
                close(fdwrite); 
                close(fdread); 
                printf("Unable to allocate memory!\n"); 
                exit(1); 
        } 
        ret = read(fdread,(void *) data, bytes); 
        if (ret == -1 || ret == 0){ 
                close(fdwrite); 
                close(fdread); 
                printf("Unable to read from %s\n",infile); 
                exit(1); 
        } 
        if (ret < bytes) 
                printf("Expected %d, read %d bytes from %s \n",bytes,ret,infile); 

        for (cp = data; cp < data + bytes; cp += sector_size){ 
                write(fdwrite, (const void *) (cp + 3), 128); 
        } 
        close(fdread); 
        close(fdwrite); 
        free(data); 

        exit(0); 
} 

