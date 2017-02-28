#include<vector>
#include<math.h>
using namespace std;
class KMeans {
public:
	KMeans(int relation_num_, int vector_dim_) {
		relation_num = relation_num_;
		vector_dim = vector_dim_;
		vector<vector<double> >cluster_center_(relation_num_, vector<double>(vector_dim_, 0));
		cluster_center.swap(cluster_center_);
		cluster_weight = __ones(relation_num_, 0);

	}
	double dist1(vector<double> vect1, vector<double> vect2) {
		double result = 0;
		for (int i = 0; i < vect1.size(); i++) {
			result += fabs(vect1[i] - vect2[i]);
		}
		return result;
	}
	double dist2(vector<double> vect1, vector<double> vect2) {
		double result = 0;
		for (int i = 0; i < vect1.size(); i++) {
			result += sqrt(vect1[i] - vect2[i]);
		}
		return result;
	}
	void fit_cluster_center(vector<vector<double> >cluster_center_, double weight) {
		cluster_center = cluster_center_;
		cluster_weight = __ones(relation_num, weight);
	}
	void fit(vector<double> vect,int  relation,double weight) {
		for (int i = 0; i < vector_dim; i++)
			cluster_center[relation][i] = (cluster_center[relation][i] * cluster_weight[relation] + vect[i] * weight) / (cluster_weight[relation] + weight);
	}
	void unfit(vector<double> vect, int  relation, double weight) {
		for (int i = 0; i < vector_dim; i++)
		{
			double tmp = cluster_center[relation][i] * cluster_weight[relation] - vect[i] * weight;
			if (tmp == 0)
				cluster_center[relation][i] = 0;
			else
				cluster_center[relation][i] = tmp / (cluster_weight[relation] - weight);
		}
	}
	vector<double> score(vector<double> vect) {
		vector<double> result(relation_num);
		for (int i = 0; i < relation_num; i++) {
			result[i] = dist1(vect, cluster_center[i]);
		}
		return result;
	}
	int predict(vector<double> vect) {
		vector<double> score_ = score(vect);
		double min_score=INFINITY;
		int best_relation = 0;
		for (int i = 0; i < relation_num; i++) {
			if (min_score > score_[i])
			{
				min_score = score_[i];
				best_relation = i;
			}
		}
		return best_relation;
	}

	void predict_and_fit(vector<double> vect, double weight, int max_iter = 10) {
		int relation = -1;
		int old_relation = -1;
		relation = predict(vect);
		fit(vect, relation, weight);
		for (int i = 0; i < max_iter; i++) {
			old_relation = relation;
			relation = predict(vect);
			if (relation == old_relation)
			{
				printf("%d",relation);
				printf("%d", i);
				return;
			}
			unfit(vect, old_relation, weight);
			fit(vect, relation, weight);
		}
	}

	vector<double> __ones(int relation_num_, double weight) {
		vector<double> result(relation_num_, weight);
		return result;
	}
	void __vector_minus_on_a(vector<double> a, vector<double> b) {
		for (int i = 0; i < a.size(); i++) {
			a[i] -= b[i];
		}
	}
private:
	int relation_num;
	int vector_dim;
	vector<vector<double> >cluster_center;
	vector<double> cluster_weight;
};







int main() {
	vector<double> a = { 1,2,3,4,5,6,7 };
	vector<double> b = { 2,1,3,5 };
	vector<vector<double> > c(100,vector<double>(100));
	KMeans kmeans(5,3);
	vector<vector<double> > centers = { {3,1,4},{5,6,9},{2,1,4},{5,2,1},{3,5,2} };
	kmeans.fit_cluster_center(centers, 25);
	vector<double> point1 = { 2,1,9 };

	vector<double>score1=kmeans.score(point1);
	printf("%d\n", kmeans.predict(point1));
	vector<double> point2 = { 3,1,7 };
	vector<double>score2 = kmeans.score(point2);
	printf("%d\n", kmeans.predict(point2));
	kmeans.predict_and_fit(point1,2);
	kmeans.predict_and_fit(point2,25);
	vector<double>test1 = kmeans.__ones(10, 0);
	vector<double> cluster_weight2(10);
	vector<double> cluster_weight(10, 20);
	b = a;
	b[1] = 6;
	return 0;
}
