#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "morceau.h"

static int	lire_ligne(char *buf, int taille)
{
	int	i;

	if (fgets(buf, taille, stdin) == NULL)
		return (-1);
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
	{
		i = getchar();
		while (i != '\n' && i != EOF)
			i = getchar();
	}
	else
		buf[i] = '\0';
	return (0);
}

static int	lire_nombre(void)
{
	char	buf[32];
	int		i;
	int		n;

	if (lire_ligne(buf, 32) == -1)
		return (-2);
	if (buf[0] == '\0')
		return (-1);
	i = 0;
	n = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		if (n > 100000000)
			return (-1);
		n = n * 10 + (buf[i] - '0');
		i++;
	}
	if (buf[i] != '\0')
		return (-1);
	return (n);
}

static void	ajouter(t_list **playlist)
{
	char		buf[128];
	t_morceau	*m;
	t_list		*node;
	int			i;
	int			pos;

	m = malloc(sizeof(t_morceau));
	if (m == NULL)
		return ;
	printf("Titre : ");
	if (lire_ligne(buf, 128) == -1)
		return (free(m));
	i = 0;
	while (i < 63 && buf[i] != '\0')
	{
		m->titre[i] = buf[i];
		i++;
	}
	m->titre[i] = '\0';
	printf("Duree en secondes : ");
	m->duree_secondes = lire_nombre();
	printf("Position (0 = en tete) : ");
	pos = lire_nombre();
	if (m->duree_secondes < 0 || pos < 0)
	{
		printf("Saisie invalide.\n");
		return (free(m));
	}
	node = ft_lstnew(m);
	if (node == NULL)
		return (free(m));
	ft_lstadd_at(playlist, node, pos);
}

static void	retirer(t_list **playlist)
{
	int	pos;

	printf("Position a retirer : ");
	pos = lire_nombre();
	if (pos < 0 || ft_lstdel_at(playlist, pos, free) == -1)
		printf("Position invalide.\n");
}

static void	afficher(t_list *playlist)
{
	t_morceau	*m;
	int			i;
	int			total;

	i = 0;
	total = 0;
	if (playlist == NULL)
		printf("Playlist vide.\n");
	while (playlist != NULL)
	{
		m = playlist->content;
		printf("%d. %s (%02d:%02d)\n", i, m->titre,
			m->duree_secondes / 60, m->duree_secondes % 60);
		total = total + m->duree_secondes;
		playlist = playlist->next;
		i++;
	}
	printf("Duree totale : %02d:%02d\n", total / 60, total % 60);
}

int	main(void)
{
	t_list	*playlist;
	int		choix;

	playlist = NULL;
	choix = 0;
	while (choix != 4)
	{
		printf("\n1. Ajouter un morceau\n2. Retirer un morceau\n");
		printf("3. Afficher la playlist\n4. Quitter\nChoix : ");
		choix = lire_nombre();
		if (choix == -2)
			choix = 4;
		else if (choix == 1)
			ajouter(&playlist);
		else if (choix == 2)
			retirer(&playlist);
		else if (choix == 3)
			afficher(playlist);
		else if (choix != 4)
			printf("Choix invalide.\n");
	}
	ft_lstclear(&playlist, free);
	return (0);
}
