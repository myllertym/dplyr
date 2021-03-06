\name{hflights_df}
\alias{hflights_df}
\alias{hflights_postgres}
\alias{hflights_sqlite}
\title{Database versions of the hflights data}
\usage{
hflights_sqlite(path = NULL)

hflights_postgres(dbname = "hflights", ...)
}
\arguments{
  \item{path}{location of sqlite database file}

  \item{dbname,...}{Arguments passed on to
  \code{\link{src_postgres}}}
}
\description{
These functions cache the data from the \code{hflights}
database in a local database, for use in examples and
vignettes.
}
\keyword{internal}

